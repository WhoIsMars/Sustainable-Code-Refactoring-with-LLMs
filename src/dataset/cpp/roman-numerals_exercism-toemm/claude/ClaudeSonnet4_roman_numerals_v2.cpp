#include "roman_numerals.h"

#include <array>
#include <string>

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
    out.reserve(16); // Reserve space to avoid reallocations
    
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
    out.reserve(16); // Reserve space to avoid reallocations
    
    static constexpr array<pair<int, char>, 7> base_symbols = {{
        {1000, 'M'}, {500, 'D'}, {100, 'C'}, {50, 'L'}, {10, 'X'}, {5, 'V'}, {1, 'I'}
    }};
    
    static constexpr array<pair<int, const char*>, 6> special_cases = {{
        {900, "CM"}, {400, "CD"}, {90, "XC"}, {40, "XL"}, {9, "IX"}, {4, "IV"}
    }};
    
    for (int divider = 1000; divider >= 1; divider /= 10) {
        int decimal = i / divider;
        if (decimal == 0) continue;
        
        int decimal_expanded = decimal * divider;
        
        // Check for special cases
        bool found_special = false;
        for (const auto& special : special_cases) {
            if (decimal_expanded == special.first) {
                out += special.second;
                i %= divider;
                found_special = true;
                break;
            }
        }
        
        if (found_special) continue;
        
        // Handle regular cases
        if (decimal >= 5) {
            // Find symbol for 5 * divider
            for (const auto& symbol : base_symbols) {
                if (symbol.first == 5 * divider) {
                    out += symbol.second;
                    break;
                }
            }
            decimal -= 5;
        }
        
        // Add remaining symbols
        for (int j = 0; j < decimal; j++) {
            for (const auto& symbol : base_symbols) {
                if (symbol.first == divider) {
                    out += symbol.second;
                    break;
                }
            }
        }
        
        i %= divider;
        if (i == 0) break;
    }
    
    return out;
}

}  // namespace roman_numerals