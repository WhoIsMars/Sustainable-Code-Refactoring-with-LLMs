#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        int count = number / numeral_map.arabic;
        if (count > 0) {
            roman_number.append(count, numeral_map.roman[0]);
            number %= numeral_map.arabic;
        }
    }
    return roman_number;
}