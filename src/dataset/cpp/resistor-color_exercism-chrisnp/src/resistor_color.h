#pragma once

#include <vector>
#include <string>

namespace resistor_color {

static const std::vector<std::string> _colors {
    "black", "brown", "red", "orange", "yellow", 
    "green", "blue", "violet", "grey", "white"
};

auto colors() noexcept -> std::vector<std::string>;
auto color_code(const std::string&) -> int;

}  // namespace resistor_color
