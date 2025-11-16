#include "roman_numerals.h"

#include <array>
#include <string_view>

namespace roman_numerals {

using namespace std;

static constexpr array<pair<string_view, int>, 13> numerals = {{
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

string convert(int i) {
    string out;
    out.reserve(16); // Reserve space for typical roman numeral length
    
    for (const auto& [numeral, value] : numerals) {
        while (i >= value) {
            out += numeral;
            i -= value;
        }
    }
    
    return out;
}

string convert_(int i) {
    string out;
    out.reserve(16); // Reserve space for typical roman numeral length
    
    // Handle thousands
    if (i >= 1000) {
        int thousands = i / 1000;
        for (int j = 0; j < thousands; ++j) {
            out += 'M';
        }
        i %= 1000;
    }
    
    // Handle hundreds
    if (i >= 100) {
        int hundreds = i / 100;
        if (hundreds == 9) {
            out += "CM";
        } else if (hundreds >= 5) {
            out += 'D';
            for (int j = 0; j < hundreds - 5; ++j) {
                out += 'C';
            }
        } else if (hundreds == 4) {
            out += "CD";
        } else {
            for (int j = 0; j < hundreds; ++j) {
                out += 'C';
            }
        }
        i %= 100;
    }
    
    // Handle tens
    if (i >= 10) {
        int tens = i / 10;
        if (tens == 9) {
            out += "XC";
        } else if (tens >= 5) {
            out += 'L';
            for (int j = 0; j < tens - 5; ++j) {
                out += 'X';
            }
        } else if (tens == 4) {
            out += "XL";
        } else {
            for (int j = 0; j < tens; ++j) {
                out += 'X';
            }
        }
        i %= 10;
    }
    
    // Handle units
    if (i >= 1) {
        if (i == 9) {
            out += "IX";
        } else if (i >= 5) {
            out += 'V';
            for (int j = 0; j < i - 5; ++j) {
                out += 'I';
            }
        } else if (i == 4) {
            out += "IV";
        } else {
            for (int j = 0; j < i; ++j) {
                out += 'I';
            }
        }
    }
    
    return out;
}

}  // namespace roman_numerals