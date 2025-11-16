#include "roman_numerals.h"

#include <string>
#include <array>

namespace roman_numerals {

using namespace std;

string convert(int i) {
    string out;
    out.reserve(15); 

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

    for (const auto& entry : numerals) {
        while (i >= entry.second) {
            out += entry.first;
            i -= entry.second;
        }
    }

    return out;
}

}  // namespace roman_numerals