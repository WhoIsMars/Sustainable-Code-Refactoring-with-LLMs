#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        if (number == 0) break;
        unsigned int count = number / numeral_map.arabic;
        if (count > 0) {
            roman_number.append(count, numeral_map.roman[0]);
            if (numeral_map.roman.size() > 1) {
                roman_number.replace(roman_number.size() - count, count, numeral_map.roman);
            }
            number %= numeral_map.arabic;
        }
    }
    return roman_number;
}