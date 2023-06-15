#include "gtest/gtest.h"
#include "GeometryUtils.h"

using namespace Geometry;
using namespace States;

namespace PolygonTest {
    TEST(PolygonTest, DefaultConstructor) {
        Polygon polygon{};
        EXPECT_EQ(polygon.getState(), States::PolygonState::NotPolygon);
        EXPECT_EQ(polygon.getPointsCopy(), std::vector<Point>());
    }

    TEST(PolygonTest, ParameterizedConstructor) {
        std::vector<Point> vec({{1,    2,    "A"},
                                {-100, 23.5, "B"}});
        Polygon polygon{vec};
        EXPECT_EQ(polygon.getPointsCopy(), vec);
        EXPECT_EQ(polygon.getState(), States::PolygonState::Edge);
    }

    TEST(PolygonTest, ParameterizedConstructorError) {

        std::vector<Point> vec = {Point(1, 2, "A"),
               Point(1, 2, "B"),
               Point(1, 2, "C")};

        EXPECT_THROW({
             try {
                 Polygon polygon = Polygon(vec);
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Points: A and B are equal!", e.what());
                 throw;
             }
       }, std::logic_error);
    }

    TEST(PolygonTest, CopyConstructor) {
        std::vector<Point> vec({{1,    2,    "A"},
                                {-100, 23.5, "B"}});
        Polygon polygon1{vec};
        Polygon polygon2{polygon1};
        EXPECT_EQ(polygon2.getState(), polygon1.getState());
        EXPECT_EQ(polygon2.getPointsCopy(), polygon1.getPointsCopy());
    }

    TEST(PolygonTest, MoveConstructor) {
        std::vector<Point> vec({{1,    2,    "A"},
                                {-100, 23.5, "B"}});
        Polygon polygon2{Polygon(vec)};
        EXPECT_EQ(polygon2.getState(), States::PolygonState::Edge);
        EXPECT_EQ(polygon2.getPointsCopy(), vec);
    }

    TEST(PolygonTest, GetVector) {
        Polygon polygon{{Point(0, 0), Point(0, 2)}};
        std::vector<Point> vec{Point(0, 0), Point(0, 2)};
        EXPECT_EQ(polygon.getPointsCopy(), vec);
        EXPECT_EQ(polygon.getPointsRef(), vec);
    }

    namespace PolygonGetStateTests {
        using test_cases_t = std::pair<std::vector<Point>, PolygonState>;
        class PolygonGetStateTestInterface : public ::testing::TestWithParam<test_cases_t> {
        protected:
            Polygon p;
        };

        TEST_P(PolygonGetStateTestInterface, GetState) {
            auto expected = std::get<1>(GetParam());
            auto input = std::get<0>(GetParam());

            p = Polygon(input);
            SCOPED_TRACE("Test");
            EXPECT_EQ(p.getState(), expected)
            << "Test: "
            << p << ".getState()"
            << "\nExpected: " << (int)expected
            << std::endl;
        }

        INSTANTIATE_TEST_SUITE_P(
                TestCases,
                PolygonGetStateTestInterface,
                ::testing::Values(
                        std::pair(std::vector<Point>{Point(0, 0), Point(0, 2), Point(3, 4)},
                                  PolygonState::Triangle),

                        std::pair(std::vector<Point>{}, PolygonState::NotPolygon),

                        std::pair(std::vector<Point>{{Point(0, 0), Point(0, 2), Point(3, 4),
                             Point(-42, -2.2), Point(-4, 53), Point(343, 1), Point(231.3, 432)}},
                                  PolygonState::OtherPolygon)
                ));
    }

    TEST(PolygonTest, EqualityOperator) {
        Polygon polygon1{{Point(0, 0), Point(0, 2), Point(3, 4)}};
        bool check_eq = polygon1 == Polygon({Point(0, 0), Point(0, 2), Point(3, 4)});
        EXPECT_EQ(check_eq, true);

        Polygon polygon2{{Point(-3, 2), Point(42, 1), Point(-4, -4)}};
        check_eq = polygon1 == polygon2;
        EXPECT_EQ(check_eq, false);
    }

    TEST(PolygonTest, InequalityOperator) {
        Polygon polygon1{{Point(0, 0), Point(0, 2), Point(3, 4)}};
        bool check_eq = polygon1 != Polygon({Point(0, 0), Point(0, 2), Point(3, 4)});
        EXPECT_EQ(check_eq, false);

        Polygon polygon2{{Point(-3, 2), Point(42, 1), Point(-4, -4)}};
        check_eq = polygon1 != polygon2;
        EXPECT_EQ(check_eq, true);
    }

    TEST(PolygonTest, AssignmentOperator) {
        Polygon polygon{};
        auto new_polygon = polygon;
        EXPECT_EQ(new_polygon, polygon);

        polygon.emplaceBack(Point(3, 2));
        new_polygon = polygon;
        EXPECT_EQ(new_polygon, polygon);

        new_polygon = Polygon({Point(3, 1), Point(-42, 42.2)});
        EXPECT_EQ(new_polygon, Polygon({Point(3, 1), Point(-42, 42.2)}));

        new_polygon = Polygon();
        EXPECT_EQ(new_polygon, Polygon());
    }

    TEST(PolygonTest, PolygonSize) {
        Polygon polygon{{Point(0, 0), Point(0, 2), Point(3, 4)}};
        EXPECT_EQ(polygon.size(), 3);

        polygon = Polygon();
        EXPECT_EQ(polygon.size(), 0);
    }

    TEST(PolygonTest, PolygonIndex) {
        Polygon polygon{{Point(0, 0), Point(0, 2), Point(3, 4)}};
        EXPECT_EQ(polygon[2], Point(3, 4));
        EXPECT_EQ(polygon[0], Point());
    }

    TEST(PolygonTest, PolygonIndexError) {
        Polygon polygon{{Point(0, 0), Point(0, 2), Point(3, 4)}};

        EXPECT_THROW({
             try {
                 Point point = polygon[4];
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Invalid index!", e.what());
                 throw;
             }
       }, std::runtime_error);

        EXPECT_THROW({
             try {
                 Point point = polygon[-1];
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Invalid index!", e.what());
                 throw;
             }
        }, std::runtime_error);
    }

    TEST(PolygonTest, EmplaceBack) {
        Polygon polygon{{Point(0, 0, "A"), Point(0, 2, "B")}};
        Point point{-2, -5, "C"};

    // Move emplace
        polygon.emplaceBack(Point(2, 0, "D"), false, false);
        EXPECT_EQ(polygon[2], Point(2, 0, "D"));

    // Ref emplace
        polygon.emplaceBack(point, false, false);
        EXPECT_EQ(polygon[3], point);
    }

    TEST(PolygonTest, emplaceBackError) {
        Polygon polygon{{Point(0, 0, "A"), Point(0, 2, "B")}};

        // Move emplace
        EXPECT_THROW({
             try {
                 polygon.emplaceBack(Point(0, 2, "F"), false, true);
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Points: B and F are equal!", e.what());
                 throw;
             }
       }, std::logic_error);

        // Logic error Emplace ref
        Point point1{0, 0, "E"};
        EXPECT_THROW({
             try {
                 polygon.emplaceBack(point1, false, true);
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Points: A and E are equal!", e.what());
                 throw;
             }
       }, std::logic_error);
    }

    TEST(PolygonTest, popBack) {
        Polygon polygon{{Point(0, 0), Point(0, 2)}};
        polygon.popBack();

        Polygon newPolygon{{Point(0, 0)}};
        EXPECT_EQ(polygon, newPolygon);

        polygon.popBack();
        EXPECT_EQ(polygon, Polygon{});
    }

    TEST(PolygonTest, popBackError) {
        Polygon newPolygon {};
        EXPECT_THROW({
             try {
                 newPolygon.popBack();
             }
             catch (const std::exception &e) {
                 EXPECT_STREQ("Polygon is empty!", e.what());
                 throw;
             }
       }, std::underflow_error);
    }

    TEST(PolygonTest, OutOperator) {
        Polygon polygon{{Point(0, 0), Point(0, 2)}};
        testing::internal::CaptureStdout();
        std::cout << polygon << std::endl;
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Polygon[(0, 0), (0, 2)]\n");

        testing::internal::CaptureStdout();
        std::cout << polygon;
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Polygon[(0, 0), (0, 2)]");
    }
}