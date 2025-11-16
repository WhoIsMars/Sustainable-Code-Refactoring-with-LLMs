#include "roman_numerals.h"

#include <string>
#include <array>
#include <utility>

namespace roman_numerals {

using namespace std;

static constexpr array<pair<const char *, int>, 13> numerals = {
    {"M", 1000},
    {"CM", 900},
    {"D", 500},
    {"CD", 400},
    {"C", 100},
    {"XC", 90},
    {"L", 50},
    {"XL", 40},
    {"X", 10},
    {"IX", 9},
    {"V", 5},
    {"IV", 4},
    {"I", 1}
};

string convert(int i) {
    string out;
    for (const auto& [symbol, value] : numerals) {
        while (i >= value) {
            out += symbol;
            i -= value;
        }
    }
    return out;
}

string convert_(int i) {
    string out;
    for (const auto& [symbol, value] : numerals) {
        int count = i / value;
        if (count > 0) {
            out.append(count, symbol[0]);
            if (symbol[1] != '\0') out.append(count, symbol[1]);
            i %= value;
        }
    }
    return out;
}

}  // namespace roman_numerals