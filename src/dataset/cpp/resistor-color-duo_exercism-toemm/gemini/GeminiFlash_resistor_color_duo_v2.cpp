#include "resistor_color_duo.h"

#include <array>

namespace resistor_color_duo {

constexpr std::array<const char*, 10> encoding{"black",  "brown", "red",  "orange",
    "yellow", "green", "blue", "violet",
    "grey",   "white"};

int color_code(const std::string& color) noexcept {
    for (std::size_t i = 0; i < encoding.size(); ++i) {
        if (color == encoding[i]) {
            return i;
        }
    }
    return 0;
}

int value(const std::vector<std::string>& input) noexcept {
    return color_code(input[0]) * 10 + color_code(input[1]);
}

}  // namespace resistor_color_duo