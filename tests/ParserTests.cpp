#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "Parsing.h"

using namespace Geometry;

TEST(ParserTest, ValidInput) {
    std::string input("(1.0, 2.0)");
    std::string result(" 1.0 2.0 ");

    // Parse the input
    std::string parsed = get<0>(Parsing::parsePoint(input));

    // Check if the parsed points match the expected points
    ASSERT_EQ(parsed, result);
}

// Test the parser with invalid input (missing comma)
TEST(ParserTest, InvalidInputMissingComma) {
    std::string input("(1.0 2.0)");

    // Parse the input
    ASSERT_EQ(get<1>(Parsing::parsePoint(input)), States::InputState::IncorrectInput);
}

// Test the parser with invalid input (missing parenthesis)
TEST(ParserTest, InvalidInputMissingParenthesis) {
    std::string input("1.0, 2.0)");

    ASSERT_EQ(get<1>(Parsing::parsePoint(input)), States::InputState::IncorrectInput);
}