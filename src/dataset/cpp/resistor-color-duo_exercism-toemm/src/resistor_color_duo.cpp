#include "resistor_color_duo.h"

#include <cmath>

namespace resistor_color_duo {

const std::vector<std::string> encoding{"black",  "brown", "red",  "orange",
    "yellow", "green", "blue", "violet",
    "grey",   "white"};

int color_code(const std::string& color) noexcept {
    for (std::size_t i{}; i < encoding.size(); i++) {
        if (encoding[i] == color) return i;
    }
    return 0;
}

int value(const std::vector<std::string>& input) noexcept {

    int val{};

    for (std::size_t i{0}, j{1}; i < 2; i++, j--) {

        auto code = color_code(input[i]);

        val += (code * std::pow(10, j));

    }

    return val;
}

}  // namespace resistor_color_duo
