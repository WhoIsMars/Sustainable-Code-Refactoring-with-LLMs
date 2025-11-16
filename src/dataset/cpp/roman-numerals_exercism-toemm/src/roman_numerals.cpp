#include "roman_numerals.h"

#include <vector>
#include <unordered_map>
#include <array>
#include <utility>

namespace roman_numerals {

using namespace std;

const unordered_map<int, string> specials    {{4, "IV"}, {9, "IX"}, {40, "XL"}, {90, "XC"}, {400, "CD"}, {900, "CM"}};
const unordered_map<int, char> table         {{1000, 'M'}, {500, 'D'}, {100, 'C'}, {50, 'L'}, {10, 'X'}, {5, 'V'}, {1, 'I'}};

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

    for (const auto& entry : numerals) {
        while (i >= entry.second) {
            out += entry.first;
            i -= entry.second;
        }
        

    }

    return out;
}

string convert_(int i) {

    string out;

    for (int divider{1000}; divider >= 1; divider /= 10) {

        int rest = i % divider;
        int decimal = i / divider;
        int decimal_expanded = decimal * divider;

        // continue to evalute next digit
        if (decimal == 0) {
            continue;
        }

        // check for special case
        auto special = specials.find(decimal_expanded);
        if (special != specials.end()) {
            out += special->second;
            i = rest;
            continue;
        }

        // 850
        if (decimal >= 5) {
            out += table.find(5 * divider)->second;
            decimal -= 5;
        }

        // 300
        // find 300 / 3 = 100 in table and write corresponding symbol
        for (int i{}; i < decimal; i++) {
            out += table.find(divider)->second;
        }

        // 3000 -> rest = 0 -> we are done
        if (rest == 0) break;
        else i = rest;

    }

    return out;


}
    


}  // namespace roman_numerals
