#include "resistor_color_duo.h"
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

namespace {
    const unordered_map<string, int> color_map = {
        {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3}, {"yellow", 4},
        {"green", 5}, {"blue", 6}, {"violet", 7}, {"grey", 8}, {"white", 9}
    };
}

auto color_code(const string& color) -> int {
    auto it = color_map.find(color);
    return it != color_map.end() ? it->second : -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors[0]) + color_code(colors[1]);
}