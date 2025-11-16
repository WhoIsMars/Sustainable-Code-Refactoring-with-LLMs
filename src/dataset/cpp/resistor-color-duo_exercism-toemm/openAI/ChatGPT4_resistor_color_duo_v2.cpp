#include "resistor_color_duo.h"

#include <unordered_map>

namespace resistor_color_duo {

const std::unordered_map<std::string, int> encoding{
    {"black", 0}, {"brown", 1}, {"red", 2},   {"orange", 3}, {"yellow", 4},
    {"green", 5}, {"blue", 6},  {"violet", 7}, {"grey", 8},  {"white", 9}};

int color_code(const std::string& color) noexcept {
    auto it = encoding.find(color);
    return (it != encoding.end()) ? it->second : 0;
}

int value(const std::vector<std::string>& input) noexcept {
    if (input.size() < 2) return 0;
    return color_code(input[0]) * 10 + color_code(input[1]);
}

}  // namespace resistor_color_duo