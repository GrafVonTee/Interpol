#include <algorithm>
#include <sstream>
#include "GeometryUtils.h"
#include "Parsing.h"

namespace Parsing {
    std::string& parseStringFromIndent(std::string &input) {
        // Replace all tabulations and delete all indent spaces from the beginning
        // Then just return the same string without indent

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

    bool isNumber(const std::string &string) {
        std::string inp = string;
        std::erase_if(inp, [](char x) { return (x == ' ') or (x == '\t') or (x == '\n'); });

        std::string::const_iterator it = inp.begin();
        bool decimalPoint = false;
        int minSize = 0;

        if (!inp.empty() && (inp[0] == '-' || inp[0] == '+')) {
            it++;
            minSize++;
        }

        while (it != inp.end()) {
            if (*it == '.') {
                if (!decimalPoint) decimalPoint = true;
                else break;
            }
            else if (!std::isdigit(*it) && ((it+1 != inp.end()) || !decimalPoint))
                break;
            ++it;
        }
        return inp.size() > minSize && it == inp.end();
    }

    // Returns a string in format " x y "
    input_result_t parsePoint(std::string &input) {
        std::stringstream parser;
        std::string result;

        // Just erase all spaces for better checking the format "(x,y)"
        std::erase_if(input, [](char x) { return (x == ' ') or (x == '\t') or (x == '\n'); });

        // Check string is empty
        if (checkStringIsEmpty(input) == States::InputState::EmptyString)
            return std::make_tuple(input, States::InputState::EmptyString);

        // Separate coordinates by comma for breaking string on "(x" and "y)"
        auto pointer_to_comma = std::find(input.begin(), input.end(), ',');
        if (pointer_to_comma == input.end())
            return std::make_tuple(input, States::InputState::IncorrectInput);

        // Just check the first template "(x"
        parser << input;
        std::getline(parser, input, ',');
        if (input[0] != '(')
            return std::make_tuple(input, States::InputState::IncorrectInput);

        // Add space in the beginning of string
        input[0] = ' ';
        if (!isNumber(input))
            return std::make_tuple(input, States::InputState::IncorrectInput);

        // Result is " input "
        result = input + " ";

        // Then check the second template "y)"
        std::getline(parser, input, ',');
        if (!input.ends_with(')'))
            return std::make_tuple(input, States::InputState::IncorrectInput);

        // Add space in the end of string
        input.back() = ' ';
        if (!isNumber(input))
            return std::make_tuple(input, States::InputState::IncorrectInput);

        // Result become " x y "
        result += input;

        return std::make_tuple(result, States::InputState::Correct);
    }
}