#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    roman_number.reserve(32); // Pre-allocate reasonable capacity
    
    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        if (numeral_map.arabic <= number) {
            unsigned int count = number / numeral_map.arabic;
            roman_number.append(count, numeral_map.roman[0]);
            if (numeral_map.roman.length() > 1) {
                for (unsigned int i = 1; i < numeral_map.roman.length(); ++i) {
                    for (unsigned int j = 0; j < count; ++j) {
                        roman_number += numeral_map.roman[i];
                    }
                }
            }
            number %= numeral_map.arabic;
        }
    }
    return roman_number;
}