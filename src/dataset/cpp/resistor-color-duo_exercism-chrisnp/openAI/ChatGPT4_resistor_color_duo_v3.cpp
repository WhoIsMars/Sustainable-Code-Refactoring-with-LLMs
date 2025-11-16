#include "resistor_color_duo.h"

using std::string;
using std::vector;

auto color_code(const string& color) -> int {
    static const auto& color_map = resistor_color_duo::colors;
    auto it = std::find(color_map.begin(), color_map.end(), color);
    return (it != color_map.end()) ? std::distance(color_map.begin(), it) : -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors[0]) + color_code(colors[1]);
}