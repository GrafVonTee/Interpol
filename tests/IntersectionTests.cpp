#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "CalculateIntersections.h"

using namespace Geometry;
using namespace Math;
using namespace States;

TEST(IntersectionTest, SingleLineIntersection) {
    // Create two triangles that intersect along a single edge
    Polygon triangle1{{Point(0, 0), Point(0, 1), Point(1, 0)}};
    Polygon triangle2{{Point(0, 0), Point(1, 0), Point(0, -1)}};

    // Compute the intersection of the triangles
    Intersection intersection = findPolygonsInter(triangle1, triangle2);

    // Check that the intersection contains a single edge
    ASSERT_EQ(intersection.polygon.size(), 2);
    ASSERT_EQ(intersection.state, States::IntersectionState::Polygon);
    EXPECT_EQ(intersection.polygon[1], Point(1, 0));
}

namespace IntersectionTests {

    struct TestInput {
        std::vector<Point> p1;
        std::vector<Point> p2;

        TestInput(std::vector<Point>&& _p1, std::vector<Point>&& _p2) {
            p1 = _p1;
            _p1.clear();
            p2 = _p2;
            _p2.clear();
        }
    };

    struct ExpectedOutput {
        size_t size;
        IntersectionState state;
        Polygon polygon;

        ExpectedOutput(size_t&& _size, IntersectionState&& _state, std::vector<Point>&& _polygon) {
            size = _size;
            _size = 0;
            state = _state;
            _state = IntersectionState::NoIntersection;
            polygon = Polygon(_polygon);
            _polygon.clear();
        }
    };


    using test_cases_t = std::pair<TestInput, ExpectedOutput>;
    class IntersectionTestsInterface : public ::testing::TestWithParam<test_cases_t> {};

    TEST_P(IntersectionTestsInterface, IntersectionType) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());
        SCOPED_TRACE("Test");

        Polygon p1{input.p1};
        Polygon p2{input.p2};

        auto intersection = findPolygonsInter(p1, p2);

        ASSERT_EQ(intersection.polygon.size(), expected.size)
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").polygon.size()\n"
        << "Expected: " << expected.size
        << "\nOutput: " << intersection.polygon.size()
        << std::endl;

        ASSERT_EQ(intersection.state, expected.state)
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").state\n"
        << "Expected: " << (int)expected.state
        << "\nOutput: " << (int)intersection.state
        << std::endl;

        EXPECT_EQ(intersection.polygon, expected.polygon)
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").polygon\n"
        << "Expected: " << expected.polygon
        << "\nOutput: " << intersection.polygon
        << std::endl;
    }

    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            IntersectionTestsInterface,
            ::testing::Values(
                    std::pair
                    (
                        TestInput({Point(0, 0, "A1"), Point(0, 2, "A2"), Point(2, 0, "A3")},
                                  {Point(0, 0, "B1"), Point(0, 3, "B2"), Point(3, 0, "B3")}),
                        ExpectedOutput(3,
                                       IntersectionState::Nested,
                                    {Point(0, 0, "C1"),
                                                              Point(0, 2, "C2"),
                                                              Point(2, 0, "C3")})
                    ),
                    std::pair
                    (
                        TestInput({Point(0, 0), Point(1, 0), Point(0, 1)},
                                  {Point(0.5, 0.5), Point(1.5, 0.5), Point(0.5, 1.5)}),
                        ExpectedOutput(1,
                                       IntersectionState::Polygon,
                                        {Point(0.5, 0.5)}
                                        )
                    ),
                    std::pair
                    (
                        TestInput({Point(100.0, 200.0), Point(100.0, 400.0), Point(300.0, 400.0)},
                                  {Point(100.0, 100.0), Point(100.0, 500.0), Point(500.0, 100.0)}),
                        ExpectedOutput(4,
                                       IntersectionState::Polygon,
                                       {Point(100, 200), Point(100, 400),
                                                Point(200, 400), Point(250, 350)}
                                      )
                    ),
            std::pair
                    (
                        TestInput({Point(-2, 2), Point(2, 2), Point(-2, -2)},
                                  {Point(4, 7), Point(3, -2), Point(2, 2)}),
                        ExpectedOutput(1,
                                       IntersectionState::Polygon,
                                       {Point(2, 2)})
                    ),
            std::pair
                    (
                        TestInput({Point(-2, 2), Point(2, 2), Point(4, -2), Point(-2, -2)},
                                  {Point(4, 7), Point(4, -2), Point(2, 2)}),
                        ExpectedOutput(2,
                                       IntersectionState::Polygon,
                                       {Point(2, 2), Point(4, -2)})
                    ),
            std::pair
                    (
                            TestInput({Point(-2, 2), Point(2, 2), Point(4, -2), Point(0, -4), Point(-2, -2)},
                                      {Point(-2, -2), Point(0, -4), Point(2, 2)}),
                            ExpectedOutput(3,
                                           IntersectionState::Polygon,
                                           {Point(-2, -2), Point(2, 2), Point(0, -4)})
                    ),
                    std::pair
                    (
                            TestInput({Point(-2, 2), Point(2, 2), Point(4, -2), Point(0, -4), Point(-2, -2)},
                                      {Point(0, 0)}),
                            ExpectedOutput(1,
                                           IntersectionState::Nested,
                                           {Point(0, 0)})
                    ),
                    std::pair
                    (
                            TestInput({Point(-2, 2), Point(2, 2), Point(4, -2), Point(0, -4), Point(-2, -2)},
                                      {Point(0, 0), Point(0, 2)}),
                            ExpectedOutput(2,
                                           IntersectionState::Nested,
                                           {Point(0, 0), Point(0, 2)})
                    )
            )
    );
};