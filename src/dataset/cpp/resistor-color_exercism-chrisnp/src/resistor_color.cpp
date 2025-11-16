#include "resistor_color.h"

using std::vector;
using std::string;

vector<string> resistor_color::colors() noexcept {
    return resistor_color::_colors;
}

int resistor_color::color_code(const string &color) {
    int value {0};
    vector<string> colors = resistor_color::colors();
    for (int i {0}; i < 10; i++) if (color == colors.at(i)) 
        value += i;
    return value;
}
