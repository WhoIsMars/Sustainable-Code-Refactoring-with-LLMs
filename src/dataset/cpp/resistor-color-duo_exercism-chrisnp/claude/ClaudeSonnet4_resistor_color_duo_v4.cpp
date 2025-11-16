#include "resistor_color_duo.h"
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

namespace {
    const unordered_map<string, int> color_map = []() {
        unordered_map<string, int> map;
        map.reserve(resistor_color_duo::colors.size());
        for (size_t i = 0; i < resistor_color_duo::colors.size(); ++i) {
            map.emplace(resistor_color_duo::colors[i], static_cast<int>(i));
        }
        return map;
    }();
}

auto color_code(const string& color) -> int {
    const auto it = color_map.find(color);
    return it != color_map.end() ? it->second : -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors[0]) + color_code(colors[1]);
}