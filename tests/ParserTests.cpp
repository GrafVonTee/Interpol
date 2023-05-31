#include "gtest/gtest.h"
#include "GeometryUtils.h"
#include "Parsing.h"

using namespace Geometry;
using namespace States;

namespace ParsesInputTests {
    using test_cases_t = std::pair<std::string, InputState>;
    class ParserInputTypeTestInterface : public ::testing::TestWithParam<test_cases_t> {};

    TEST_P(ParserInputTypeTestInterface, InputTypeTest) {
        auto expected = std::get<1>(GetParam());
        auto input = std::get<0>(GetParam());
        SCOPED_TRACE("Test");

        auto s = input;
        auto res = Parsing::parsePoint(input);

        ASSERT_EQ(get<1>(res), expected)
        << "Test: "
        << "get<1>Parsing::parsePoint(" << s << ")\n"
        << "Expected State: " << (int)expected << "\n"
        << "Output string: " << get<0>(res)
        << std::endl;
    }

    INSTANTIATE_TEST_SUITE_P(
            TestCases,
            ParserInputTypeTestInterface,
            ::testing::Values(
                    std::pair("(1.0, 2.0)", InputState::Correct),
                    std::pair("(1,0, 2,0)", InputState::IncorrectInput),
                    std::pair("(1.0 2.0)", InputState::IncorrectInput),
                    std::pair("1.0, 2.0)", InputState::IncorrectInput),
                    std::pair("[1.0, 2.0]", InputState::IncorrectInput),
                    std::pair("(1.0. 2.0)", InputState::IncorrectInput),
                    std::pair("(1.0, 2.0", InputState::IncorrectInput),
                    std::pair("1.0, 2.0", InputState::IncorrectInput),

                    std::pair("", InputState::EmptyString),
                    std::pair("     ", InputState::EmptyString),
                    std::pair("                                                                                 ",
                              InputState::EmptyString),

                    std::pair("()", InputState::IncorrectInput),
                    std::pair("(            312.324,               3231 )", InputState::Correct),
                    std::pair("(3123,         123.242141241)", InputState::Correct),
                    std::pair("(       -0.00213,        -100.081)", InputState::Correct),
                    std::pair("(-0.00213,       100)", InputState::Correct),
                    std::pair("(-0.00213    ,    100)", InputState::Correct),
                    std::pair("(0.00000, 0)", InputState::Correct),

                    std::pair("( , )", InputState::IncorrectInput),
                    std::pair("(323, )", InputState::IncorrectInput),
                    std::pair("( , -0.424)", InputState::IncorrectInput),
                    std::pair("(-, -10)", InputState::IncorrectInput),
                    std::pair("(- , )", InputState::IncorrectInput),

                    std::pair("( , +)", InputState::IncorrectInput),
                    std::pair("(+, -)", InputState::IncorrectInput),
                    std::pair("((2, 3), (2, 1))", InputState::IncorrectInput),
                    std::pair("(10a, 10b)", InputState::IncorrectInput),
                    std::pair("(--10, --200.32)", InputState::IncorrectInput),
                    std::pair("(+-10, -10)", InputState::IncorrectInput),
                    std::pair("(+10, +313.43)", InputState::Correct),
                    std::pair("(*10, +313.43)", InputState::IncorrectInput),
                    std::pair("(яПанк, 10)", InputState::IncorrectInput),
                    std::pair("(-10, -)", InputState::IncorrectInput),
                    std::pair("(-, -)", InputState::IncorrectInput),
                    std::pair("(*, *)", InputState::IncorrectInput),
                    std::pair("(dsfsfds321f, fdfdfsd32ds)", InputState::IncorrectInput),
                    std::pair("(0.45, 1)", InputState::Correct),
                    std::pair("(-0.00213, 100)", InputState::Correct),
                    std::pair("(100000000000000000100000000000000000.04342,"
                              "100000000000000000100000000000000000.04324)", InputState::Correct),
                    std::pair("(100000000000000000, 10000000000000000)", InputState::Correct)
            ));
}