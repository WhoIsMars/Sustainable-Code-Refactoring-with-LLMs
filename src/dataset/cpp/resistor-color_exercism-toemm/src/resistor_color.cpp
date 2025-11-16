#include "resistor_color.h"

namespace resistor_color {

const std::vector<std::string> encoding{"black",  "brown", "red",  "orange",
                                        "yellow", "green", "blue", "violet",
                                        "grey",   "white"};

int color_code(const std::string& color) noexcept {
    for (std::size_t i{}; i < encoding.size(); i++) {
        if (encoding[i] == color) return i;
    }
    return 0;
}

std::vector<std::string> colors() noexcept {
    return encoding;
}

}  // namespace resistor_color
