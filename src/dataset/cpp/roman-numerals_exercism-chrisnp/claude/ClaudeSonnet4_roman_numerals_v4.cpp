#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    roman_number.reserve(32);

    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        const unsigned int count = number / numeral_map.arabic;
        if (count > 0) {
            roman_number.append(count, numeral_map.roman[0]);
            if (numeral_map.roman.length() > 1) {
                for (unsigned int i = 1; i < count; ++i) {
                    roman_number += numeral_map.roman.substr(1);
                }
            }
            number -= count * numeral_map.arabic;
        }
    }
    return roman_number;
}