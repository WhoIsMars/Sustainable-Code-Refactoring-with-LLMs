#include "roman_numerals.h"

#include <string>
#include <array>

namespace roman_numerals {

using namespace std;

static constexpr array<pair<int, const char *>, 13> numerals = {
    std::make_pair(1000, "M"),
    std::make_pair(900, "CM"),
    std::make_pair(500, "D"),
    std::make_pair(400, "CD"),
    std::make_pair(100, "C"),
    std::make_pair(90, "XC"),
    std::make_pair(50, "L"),
    std::make_pair(40, "XL"),
    std::make_pair(10, "X"),
    std::make_pair(9, "IX"),
    std::make_pair(5, "V"),
    std::make_pair(4, "IV"),
    std::make_pair(1, "I")
};

string convert(int number) {
    string result;
    result.reserve(16); // Pre-allocate memory to avoid reallocations

    for (const auto& numeral : numerals) {
        while (number >= numeral.first) {
            result += numeral.second;
            number -= numeral.first;
        }
    }

    return result;
}

}  // namespace roman_numerals