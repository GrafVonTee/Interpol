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

    enum class ExpectedItems { Size, State, InterPolygon };

    using pair_vec_t = std::pair<std::vector<Point>, std::vector<Point>>;
    using expected_value_t = std::tuple<size_t, IntersectionState, Polygon>;

    using test_cases_t = std::pair<pair_vec_t, expected_value_t>;
    class IntersectionTestsInterface : public ::testing::TestWithParam<test_cases_t> {};

    TEST_P(IntersectionTestsInterface, IntersectionType) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());
        SCOPED_TRACE("Test");

        Polygon p1{input.first};
        Polygon p2{input.second};

        auto intersection = findPolygonsInter(p1, p2);

        ASSERT_EQ(intersection.polygon.size(), std::get<(int)ExpectedItems::Size>(expected))
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").polygon.size()\n"
        << "Expected: " << std::get<int(ExpectedItems::Size)>(expected)
        << "\nOutput: " << intersection.polygon.size()
        << std::endl;

        ASSERT_EQ(intersection.state, std::get<(int)ExpectedItems::State>(expected))
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").state\n"
        << "Expected: " << (int)std::get<int(ExpectedItems::State)>(expected)
        << "\nOutput: " << (int)intersection.state
        << std::endl;

        EXPECT_EQ(intersection.polygon, std::get<(int)ExpectedItems::InterPolygon>(expected))
        << "Test: " << "findPolygonsInter(" << p1 << ", " << p2 << ").polygon\n"
        << "Expected: " << std::get<int(ExpectedItems::InterPolygon)>(expected)
        << "\nOutput: " << intersection.polygon
        << std::endl;
    }

    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            IntersectionTestsInterface,
            ::testing::Values(
                    std::pair
                    (
                        std::pair // Input
                        (
                            std::vector<Point>{Point(0, 0, "A1"), Point(0, 2, "A2"), Point(2, 0, "A3")},
                            std::vector<Point>{Point(0, 0, "B1"), Point(0, 3, "B2"), Point(3, 0, "B3")}
                        ),
                        std::make_tuple // Expected
                        (   3,
                            IntersectionState::Nested,
                            Polygon{{Point(0, 0, "C1"), Point(0, 2, "C2"), Point(2, 0, "C3")}}
                        )
                    ),
                    std::pair
                    (
                        std::pair // Input
                        (
                            std::vector<Point>{Point(0, 0), Point(1, 0), Point(0, 1)},
                            std::vector<Point>{Point(0.5, 0.5), Point(1.5, 0.5), Point(0.5, 1.5)}
                        ),
                        std::make_tuple // Expected
                        (   1,
                            IntersectionState::Polygon,
                            Polygon{{Point(0.5, 0.5)}}
                        )
                    ),
                    std::pair
                    (
                    std::pair // Input
                        (
                            std::vector<Point>{Point(100.0, 200.0), Point(100.0, 400.0), Point(300.0, 400.0)},
                            std::vector<Point>{Point(100.0, 100.0), Point(100.0, 500.0), Point(500.0, 100.0)}
                        ),
                    std::make_tuple // Expected
                        (
                            4,
                            IntersectionState::Polygon,
                            Polygon{{Point(100, 200), Point(100, 400),
                                           Point(200, 400), Point(250, 350)}
                            }
                        )
                    )
            )
    );
}