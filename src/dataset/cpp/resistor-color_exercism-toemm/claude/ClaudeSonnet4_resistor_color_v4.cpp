#include "resistor_color.h"
#include <unordered_map>

namespace resistor_color {

constexpr std::array<const char*, 10> encoding_array{
    "black", "brown", "red", "orange", "yellow",
    "green", "blue", "violet", "grey", "white"
};

const std::unordered_map<std::string_view, int> color_map{
    {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3}, {"yellow", 4},
    {"green", 5}, {"blue", 6}, {"violet", 7}, {"grey", 8}, {"white", 9}
};

int color_code(const std::string& color) noexcept {
    auto it = color_map.find(color);
    return it != color_map.end() ? it->second : 0;
}

std::vector<std::string> colors() noexcept {
    return {encoding_array.begin(), encoding_array.end()};
}

}  // namespace resistor_color