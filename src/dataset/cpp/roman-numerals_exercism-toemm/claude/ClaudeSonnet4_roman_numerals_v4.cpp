#include "roman_numerals.h"

#include <string>
#include <array>

namespace roman_numerals {

static constexpr std::array<std::pair<int, const char*>, 13> numerals = {{
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
}};

std::string convert(int i) {
    std::string result;
    result.reserve(16);
    
    for (const auto& [value, numeral] : numerals) {
        while (i >= value) {
            result += numeral;
            i -= value;
        }
    }
    
    return result;
}

std::string convert_(int i) {
    std::string result;
    result.reserve(16);
    
    static constexpr std::array<int, 4> dividers = {1000, 100, 10, 1};
    static constexpr std::array<const char*, 4> five_symbols = {"", "D", "L", "V"};
    static constexpr std::array<const char*, 4> one_symbols = {"M", "C", "X", "I"};
    static constexpr std::array<std::pair<int, const char*>, 6> specials = {{
        {900, "CM"}, {400, "CD"}, {90, "XC"}, {40, "XL"}, {9, "IX"}, {4, "IV"}
    }};
    
    for (int idx = 0; idx < 4; ++idx) {
        const int divider = dividers[idx];
        const int decimal = i / divider;
        
        if (decimal == 0) continue;
        
        const int decimal_expanded = decimal * divider;
        i %= divider;
        
        for (const auto& [special_val, special_str] : specials) {
            if (decimal_expanded == special_val) {
                result += special_str;
                goto next_digit;
            }
        }
        
        if (decimal >= 5) {
            result += five_symbols[idx];
            const int remaining = decimal - 5;
            for (int j = 0; j < remaining; ++j) {
                result += one_symbols[idx];
            }
        } else {
            for (int j = 0; j < decimal; ++j) {
                result += one_symbols[idx];
            }
        }
        
        next_digit:
        if (i == 0) break;
    }
    
    return result;
}

}  // namespace roman_numerals