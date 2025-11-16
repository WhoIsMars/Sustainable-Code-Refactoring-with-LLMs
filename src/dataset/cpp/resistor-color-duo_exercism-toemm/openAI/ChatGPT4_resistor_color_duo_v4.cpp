#include "resistor_color_duo.h"

#include <array>
#include <unordered_map>

namespace resistor_color_duo {

constexpr std::array<const char*, 10> encoding{
    "black", "brown", "red", "orange", "yellow", 
    "green", "blue", "violet", "grey", "white"};

constexpr std::unordered_map<std::string_view, int> encoding_map = [] {
    std::unordered_map<std::string_view, int> map;
    for (std::size_t i = 0; i < encoding.size(); ++i) {
        map[encoding[i]] = static_cast<int>(i);
    }
    return map;
}();

constexpr int color_code(std::string_view color) noexcept {
    auto it = encoding_map.find(color);
    return it != encoding_map.end() ? it->second : 0;
}

int value(const std::vector<std::string>& input) noexcept {
    return color_code(input[0]) * 10 + color_code(input[1]);
}

}  // namespace resistor_color_duo