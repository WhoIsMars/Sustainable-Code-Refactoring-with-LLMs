#include "resistor_color_duo.h"

using std::string;
using std::vector;

auto color_code(const string& color) -> int {
    static const auto& color_map = resistor_color_duo::colors;
    for (size_t i = 0; i < color_map.size(); ++i)
        if (color_map[i] == color) return i;
    return -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors[0]) + color_code(colors[1]);
}