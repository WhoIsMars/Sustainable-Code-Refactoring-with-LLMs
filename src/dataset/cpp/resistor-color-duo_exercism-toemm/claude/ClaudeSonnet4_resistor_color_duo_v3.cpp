#include "resistor_color_duo.h"

#include <unordered_map>

namespace resistor_color_duo {

const std::unordered_map<std::string, int> color_map{
    {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3},
    {"yellow", 4}, {"green", 5}, {"blue", 6}, {"violet", 7},
    {"grey", 8}, {"white", 9}
};

int color_code(const std::string& color) noexcept {
    auto it = color_map.find(color);
    return (it != color_map.end()) ? it->second : 0;
}

int value(const std::vector<std::string>& input) noexcept {
    return color_code(input[0]) * 10 + color_code(input[1]);
}

}  // namespace resistor_color_duo