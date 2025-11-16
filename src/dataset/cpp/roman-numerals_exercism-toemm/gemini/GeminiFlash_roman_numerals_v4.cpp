#include "roman_numerals.h"

#include <string>
#include <array>

namespace roman_numerals {

using namespace std;

string convert(int i) {
    string out;
    out.reserve(16); 

    static constexpr array<pair<int, const char*>, 13> numerals = {
        {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
         {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}}
    };

    for (const auto& entry : numerals) {
        while (i >= entry.first) {
            out += entry.second;
            i -= entry.first;
        }
    }

    return out;
}

string convert_(int i) {
    string out;
    out.reserve(16);

    static constexpr array<pair<int, const char*>, 13> numerals = {
        {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
         {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}}
    };

    for (const auto& entry : numerals) {
        while (i >= entry.first) {
            out += entry.second;
            i -= entry.first;
        }
    }

    return out;
}

}  // namespace roman_numerals