#ifndef TRIANGLE_INTERSECTIONS_PARSING_H
#define TRIANGLE_INTERSECTIONS_PARSING_H

namespace Parsing {
    using input_result_t = std::tuple<std::string, States::InputState>;

    std::string& parseStringFromIndent(std::string &input);
    States::InputState checkStringIsEmpty(const std::string &input);
    input_result_t parsePoint(std::string &input);
}

#endif //TRIANGLE_INTERSECTIONS_PARSING_H
