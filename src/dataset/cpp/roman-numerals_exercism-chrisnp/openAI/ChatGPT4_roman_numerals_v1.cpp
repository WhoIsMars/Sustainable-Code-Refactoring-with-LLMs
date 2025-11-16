#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        while (number >= numeral_map.arabic) {
            roman_number.append(numeral_map.roman);
            number -= numeral_map.arabic;
        }
        if (number == 0) break;
    }
    return roman_number;
}