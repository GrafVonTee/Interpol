#include <gtest/gtest.h>
#include "CalculateIntersections.h"

using namespace Math;

namespace DeterminantTest {
    using test_cases_t = std::pair<std::vector<coord_t>, coord_t>;
    class DeterminantTestInterface : public ::testing::TestWithParam<test_cases_t> {};

    TEST_P(DeterminantTestInterface, CalculateDet) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());

        SCOPED_TRACE("Test");

        coord_t ans = det(input[0], input[1],input[2], input[3]);

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