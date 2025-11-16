#include "roman_numerals.h"

#include <string>
#include <array>
#include <utility>

namespace roman_numerals {

using namespace std;

static constexpr array<pair<const char *, int>, 13> numerals = {
    std::make_pair("M", 1000),
    std::make_pair("CM", 900),
    std::make_pair("D", 500),
    std::make_pair("CD", 400),
    std::make_pair("C", 100),
    std::make_pair("XC", 90),
    std::make_pair("L", 50),
    std::make_pair("XL", 40),
    std::make_pair("X", 10),
    std::make_pair("IX", 9),
    std::make_pair("V", 5),
    std::make_pair("IV", 4),
    std::make_pair("I", 1)
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
        while (i >= value) {
            out += symbol;
            i -= value;
        }
    }
    return out;
}

}  // namespace roman_numerals