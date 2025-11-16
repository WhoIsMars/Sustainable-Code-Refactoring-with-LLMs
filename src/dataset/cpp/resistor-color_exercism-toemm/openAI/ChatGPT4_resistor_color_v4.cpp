#include "resistor_color.h"
#include <unordered_map>

namespace resistor_color {

const std::unordered_map<std::string, int> encoding_map{
    {"black", 0},  {"brown", 1}, {"red", 2},    {"orange", 3},
    {"yellow", 4}, {"green", 5}, {"blue", 6},   {"violet", 7},
    {"grey", 8},   {"white", 9}};

const std::vector<std::string> encoding{
    "black", "brown", "red", "orange", "yellow",
    "green", "blue", "violet", "grey", "white"};

int color_code(const std::string& color) noexcept {
    auto it = encoding_map.find(color);
    return it != encoding_map.end() ? it->second : 0;
}

const std::vector<std::string>& colors() noexcept {
    return encoding;
}

}  // namespace resistor_color