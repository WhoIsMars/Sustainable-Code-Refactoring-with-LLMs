#include "resistor_color_duo.h"

using std::string;
using std::vector;
using std::unordered_map;

namespace {
    const unordered_map<string, int> color_map = [] {
        unordered_map<string, int> map;
        for (size_t i = 0; i < resistor_color_duo::colors.size(); ++i) {
            map[resistor_color_duo::colors[i]] = i;
        }
        return map;
    }();
}

auto color_code(const string& color) -> int {
    auto it = color_map.find(color);
    return it != color_map.end() ? it->second : -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors[0]) + color_code(colors[1]);
}