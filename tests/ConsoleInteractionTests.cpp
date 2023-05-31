#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"

using namespace Geometry;
using namespace Interaction;

TEST(ConsoleInteraction, ValidInputFormat) {
    std::istringstream input("(1.0, 2.0)\n");
    Point point = get<0>(getPoint("A", input));
    ASSERT_EQ(point, Point(1.0, 2.0));
}

TEST(ConsoleInteraction, InvalidInputFormatPoint) {
    std::istringstream input("1,2\n(3.0, 4.0)\n");
    testing::internal::CaptureStderr();
    Point point = get<0>(getPoint("A", input));
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\n");
    ASSERT_EQ(point, Point(0.0, 0.0));
}

TEST(ConsoleInteraction, EmptyString) {
    std::istringstream input("\n(3.0, 4.0)\n");
    testing::internal::CaptureStderr();
    Point point = get<0>(getPoint("A", input));
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "String is empty! Please, enter values in format '(x, y)'!\n");
    ASSERT_EQ(point, Point(0.0, 0.0));
}

TEST(ConsoleInteraction, ReenteredInvalidInputFormatTriangle) {
    std::istringstream input("1,2\n(3.0, 4.0)\n(1.0, 2.0)\n1,2\n(1.0, 4.0)\n");
    testing::internal::CaptureStderr();
    Polygon triangle = get<0>(getTriangle("A", input));
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output,
              "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\n"
              "Incorrect input! Please, enter values in CORRECT format '(x, y)'!\n");
    EXPECT_EQ(triangle.size(), 3);
    ASSERT_EQ(triangle[0], Point(1.0, 2.0));
    ASSERT_EQ(triangle[1], Point(1.0, 4.0));
    ASSERT_EQ(triangle[2], Point(3.0, 4.0));
}

TEST(ConsoleInteraction, SamePointsTriangle) {
    std::istringstream input("(3.0, 4.0)\n(1.0, 2.0)\n(3.0, 4.0)\n");
    testing::internal::CaptureStderr();
    Polygon triangle = get<0>(getTriangle("A", input));
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Points: A1 and A3 are equal!\n");
}

TEST(ConsoleInteraction, NotATriangle) {
    std::istringstream input("(0.0, 0.0)\n(0.0, 2.0)\n(0.0, 4.0)\n");
    testing::internal::CaptureStderr();
    Polygon triangle = get<0>(getTriangle("A", input));
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Points: A3, A1, A2 are located in one line!\n");
}