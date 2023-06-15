#include <gtest/gtest.h>
#include "CalculateIntersections.h"

using namespace Math;
using namespace Geometry;

namespace MathTest {
    namespace DeterminantTest {
        using test_cases_t = std::pair<std::vector<coord_t>, coord_t>;

        class DeterminantTestInterface : public ::testing::TestWithParam<test_cases_t> {};

        TEST_P(DeterminantTestInterface, CalculateDet) {
            auto expected = std::get<1>(GetParam());
            auto input = std::get<0>(GetParam());

            SCOPED_TRACE("Test");

            coord_t ans = det(input[0], input[1], input[2], input[3]);

            EXPECT_EQ(expected, ans)
                                << "Test: det(" << input[0] << ", " << input[1]
                                << ", " << input[2] << ", " << input[3]
                                << ")\n"
                                << "Expected: " << expected
                                << "\nOutput: " << ans
                                << std::endl;
        }

        INSTANTIATE_TEST_SUITE_P(
                TestCases,
                DeterminantTestInterface,
                ::testing::Values(
                        std::pair(std::vector<coord_t>{0, 0, 0, 0}, 0),
                        std::pair(std::vector<coord_t>{1, 2, 2, 1}, -3)
                )
        );
    }
    namespace InsidePointTest {
        struct TestInput {
            Polygon polygon {};
            Point point {};

            TestInput(std::vector<Point>&& vec, Point&& _point) {
                polygon = Polygon(vec);
                point = std::move(_point);
            }
        };

        using test_cases_t = std::pair<TestInput, bool>;
        class InsidePointTestInterface : public ::testing::TestWithParam<test_cases_t> {};

        TEST_P(InsidePointTestInterface, CalculateDet) {
            auto expected = std::get<1>(GetParam());
            auto input = std::get<0>(GetParam());
            SCOPED_TRACE("Test");

            bool ans = isPointInside(input.point, input.polygon);

            ASSERT_EQ(ans, expected)
            << "Test: isPointInside(" << input.point << ", " << input.polygon << ")\n"
            << "Expected: " << expected
            << "\nOutput: " << ans
            << std::endl;
        }

        INSTANTIATE_TEST_SUITE_P(
                TestCases,
                InsidePointTestInterface,
                ::testing::Values(
                        std::pair(TestInput({}, Point()), false),

                        std::pair(TestInput({Point(2, 2), Point(2, -2),
                                             Point(-2, 2), Point(-2, -2)},
                                            Point()), true),

                        std::pair(TestInput({Point(2, 2), Point(2, -2),
                                             Point(-2, 2), Point(-2, -2)},
                                            Point(3, 3)), false),

                        std::pair(TestInput({Point(2, 2), Point(2, -2),
                                             Point(-2, 2), Point(-2, -2)},
                                            Point(3, 3)), false),

                        std::pair(TestInput({Point(-2, 0), Point(2, 0),
                                             Point(2, 2)},
                                            Point(1, 1)), true),

                        std::pair(TestInput({Point(2, 0), Point(-2, 0)},
                                            Point(0, 0)), true),

                        std::pair(TestInput({Point(2, 2), Point(2, -2),
                                             Point(-2, 2), Point(-2, -2)},
                                            Point(2, 2)), true),

                        std::pair(TestInput({Point()}, Point()), true)
                )
        );
    }
}