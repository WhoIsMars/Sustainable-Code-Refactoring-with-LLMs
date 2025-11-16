#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {

    string roman_number;

    for (auto numeral_map : roman_numerals::arabic_to_roman) {
        while (numeral_map.arabic <= number) {
            roman_number += numeral_map.roman;
            number -= numeral_map.arabic;
        }
    }
    return roman_number;
}