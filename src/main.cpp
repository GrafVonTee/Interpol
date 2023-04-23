#include <iostream>
#include "StructUtils.h"

int main() {
    Utils::Point a {3, 9};
    Utils::Point b {1, 2};

    Utils::Edge e {a, b};

    std::cout << e << std::endl;
    std::cout << e.length() << std::endl;
    return 0;
}