#include "roman_numerals.h"

#include <string>
#include <array>
#include <utility>

namespace roman_numerals {

using namespace std;

static constexpr array<pair<const char*, int>, 13> numerals = {{
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
}};

static constexpr array<pair<int, char>, 7> table = {{
    {1000, 'M'},
    {500, 'D'},
    {100, 'C'},
    {50, 'L'},
    {10, 'X'},
    {5, 'V'},
    {1, 'I'}
}};

static constexpr array<pair<int, const char*>, 6> specials = {{
    {900, "CM"},
    {400, "CD"},
    {90, "XC"},
    {40, "XL"},
    {9, "IX"},
    {4, "IV"}
}};

string convert(int i) {
    string out;
    out.reserve(16);
    
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
    out.reserve(16);
    
    for (int divider = 1000; divider >= 1; divider /= 10) {
        const int rest = i % divider;
        const int decimal = i / divider;
        const int decimal_expanded = decimal * divider;
        
        if (decimal == 0) {
            continue;
        }
        
        for (const auto& special : specials) {
            if (decimal_expanded == special.first) {
                out += special.second;
                i = rest;
                goto next_digit;
            }
        }
        
        if (decimal >= 5) {
            for (const auto& entry : table) {
                if (entry.first == 5 * divider) {
                    out += entry.second;
                    break;
                }
            }
        }
        
        const int remaining_decimal = decimal >= 5 ? decimal - 5 : decimal;
        for (int j = 0; j < remaining_decimal; ++j) {
            for (const auto& entry : table) {
                if (entry.first == divider) {
                    out += entry.second;
                    break;
                }
            }
        }
        
        if (rest == 0) break;
        i = rest;
        
        next_digit:;
    }
    
    return out;
}

}  // namespace roman_numerals