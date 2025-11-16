#include "resistor_color.h"
#include <unordered_map>

namespace resistor_color {

const std::unordered_map<std::string, int> encoding{
    {"black", 0},  {"brown", 1}, {"red", 2},    {"orange", 3}, {"yellow", 4},
    {"green", 5},  {"blue", 6},  {"violet", 7}, {"grey", 8},   {"white", 9}};

int color_code(const std::string& color) noexcept {
    auto it = encoding.find(color);
    return (it != encoding.end()) ? it->second : 0;
}

std::vector<std::string> colors() noexcept {
    std::vector<std::string> color_list(encoding.size());
    for (const auto& pair : encoding) {
        color_list[pair.second] = pair.first;
    }
    return color_list;
}

}  // namespace resistor_color