#include <iostream>
#include <string>
#include "StatesUtils.h"
#include "Parsing.h"

namespace Parsing {
    std::string parseStringFromIndent(std::string input) {
        auto indent = input.find_first_not_of(' ');
        input = input.substr(indent);
        indent = input.find_first_not_of('\t');
        input = input.substr(indent);
        return input;
    }

    States::InputState checkStringIsEmpty(const std::string input) {
        return (input.empty()) ? States::InputState::IncorrectInput : States::InputState::Correct;
    }
}
