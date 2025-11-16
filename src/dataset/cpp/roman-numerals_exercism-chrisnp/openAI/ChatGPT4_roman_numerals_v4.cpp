#include "roman_numerals.h"

using namespace std;

string roman_numerals::convert(unsigned int number) {
    string roman_number;
    roman_number.reserve(20); // Reserve space to minimize reallocations

    for (const auto& numeral_map : roman_numerals::arabic_to_roman) {
        while (number >= numeral_map.arabic) {
            roman_number.append(numeral_map.roman);
            number -= numeral_map.arabic;
        }
        if (number == 0) break; // Exit early if number is fully converted
    }
    return roman_number;
}