#include <string>
#include <algorithm>
#include <tuple>
#include "GeometryUtils.h"
#include "Parsing.h"
#include <sstream>

namespace Parsing {
    std::string& parseStringFromIndent(std::string &input) {
        auto iter = input.find('\t');
        while (((iter = input.find('\t')) != std::string::npos)) {
            input.replace(iter, 1, " ");
        }
        auto indent = input.find_first_not_of(' ');
        if (indent != std::string::npos)
            input = input.substr(indent);
        else
            input = "";
        return input;
    }

    States::InputState checkStringIsEmpty(const std::string &input) {
        return (input.empty()) ? States::InputState::EmptyString : States::InputState::Correct;
    }

    bool isNumber(const std::string &s) {
        coord_t newVariable;
        return (std::istringstream(s) >> newVariable >> std::ws).eof();
    }

    input_result_t parsePoint(std::string &input) {
        std::stringstream parser;
        std::string result;

        std::erase_if(input, [](char x) { return (x == ' ') or (x == '\t') or (x == '\n'); });

        auto pointer_to_comma = std::find(input.begin(), input.end(), ',');
        if (pointer_to_comma == input.end())
            return std::make_tuple(input, States::InputState::IncorrectFormat);

        parser << input;
        std::getline(parser, input, ',');
        if (input[0] != '(')
            return std::make_tuple(input, States::InputState::IncorrectFormat);

        input[0] = ' ';
        if (!isNumber(input))
            return std::make_tuple(input, States::InputState::IncorrectInput);

        result = input + " ";

        std::getline(parser, input, ',');
        if (!input.ends_with(')'))
            return std::make_tuple(input, States::InputState::IncorrectFormat);

        input.back() = ' ';
        if (!isNumber(input))
            return std::make_tuple(input, States::InputState::IncorrectInput);

        result += input;

        return std::make_tuple(result, States::InputState::Correct);
    }
}
