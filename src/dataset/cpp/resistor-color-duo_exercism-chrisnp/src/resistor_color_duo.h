#pragma once

#include<vector>
#include<string>

namespace resistor_color_duo {

const std::vector<std::string> colors {
    "black", "brown", "red", "orange", "yellow",
    "green", "blue", "violet", "grey", "white"
};

auto value(const std::vector<std::string>&) -> int;

}  // namespace resistor_color_duo


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
