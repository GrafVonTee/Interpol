#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"

using namespace Geometry;
using namespace Interaction;

namespace InteractionTests {
    TEST(ConsoleInteraction, ValidInputFormat) {
        std::istringstream input("(1.0, 2.0)\n");
        std::ostringstream output("");
        Point point = get<0>(getPoint("A", input, output));
        ASSERT_EQ(point, Point(1.0, 2.0));
    }

    TEST(ConsoleInteraction, InvalidInputFormatPoint) {
        std::istringstream input("1,2\n(3.0, 4.0)\n");
        std::ostringstream outputStream("");

        testing::internal::CaptureStderr();
        Point point = get<0>(getPoint("A", input, outputStream));
        std::string output = testing::internal::GetCapturedStderr();
        EXPECT_EQ(output, "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\n");
        ASSERT_EQ(point, Point(0.0, 0.0));
    }

    TEST(ConsoleInteraction, EmptyString) {
        std::istringstream input("\n(3.0, 4.0)\n");
        std::ostringstream outputStream("");

        testing::internal::CaptureStderr();
        Point point = get<0>(getPoint("A", input, outputStream));
        std::string output = testing::internal::GetCapturedStderr();
        EXPECT_EQ(output, "String is empty! Please, enter values in format '(x, y)'!\n");
        ASSERT_EQ(point, Point(0.0, 0.0));
    }
}