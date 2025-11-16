#include "resistor_color_duo.h"

using std::string;
using std::vector;

auto color_code(const string& color) -> int {
    for (size_t i {}; i <= resistor_color_duo::colors.size(); ++i)
        if(resistor_color_duo::colors.at(i) == color) return i;
    return -1;
}

int resistor_color_duo::value(const vector<string>& colors) {
    return 10 * color_code(colors.at(0)) + color_code(colors.at(1));
}
