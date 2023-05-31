#include "gtest/gtest.h"
#include "GeometryUtils.h"

using namespace Geometry;

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

    vec = {Point(1, 2, "A"),
           Point(1, 2, "B"),
           Point(1, 2, "C")};

    EXPECT_THROW({
         try {
             polygon = Polygon(vec);
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

TEST(PolygonTest, GetState) {
    Polygon polygon1{{Point(0, 0), Point(0, 2), Point(3, 4)}};
    EXPECT_EQ(polygon1.getState(), States::PolygonState::Triangle);

    Polygon polygon2{};
    EXPECT_EQ(polygon2.getState(), States::PolygonState::NotPolygon);

    Polygon polygon3{{Point(0, 0), Point(0, 2), Point(3, 4),
                      Point(-42, -2.2), Point(-4, 53), Point(343, 1),
                      Point(231.3, 432)}};
    EXPECT_EQ(polygon3.getState(), States::PolygonState::OtherPolygon);
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

TEST(Polygon, AssignmentOperator) {
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

// Index out of a range
    EXPECT_THROW({
         try {
             Point point = polygon[4];
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

// Logic error Emplace move
    EXPECT_THROW({
         try {
             polygon.emplaceBack(Point(2, 0, "F"), false, true);
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Points: D and F are equal!", e.what());
             throw;
         }
   }, std::logic_error);

// Logic error Emplace ref
    Point point1{-2, -5, "F"};
    EXPECT_THROW({
         try {
             polygon.emplaceBack(point1, false, true);
         }
         catch (const std::exception &e) {
             EXPECT_STREQ("Points: C and F are equal!", e.what());
             throw;
         }
   }, std::logic_error);
}

TEST(PolygonTest, popBack) {
    Polygon polygon{{Point(0, 0), Point(0, 2)}};
    polygon.popBack();

    Polygon newPolygon{{Point(0, 0)}};
    EXPECT_EQ(polygon, newPolygon);

    newPolygon.popBack();

// size == 0 popBack
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
    EXPECT_EQ(output, "Polygon[(0, 0, ), (0, 2, )]\n");

    testing::internal::CaptureStdout();
    std::cout << polygon;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Polygon[(0, 0, ), (0, 2, )]");
}