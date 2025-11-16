#include "say.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <array>

namespace say {

    static const std::array<std::string, 20> ones = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    static const std::array<std::string, 8> tens = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    std::string in_english(long long number) {
        if (number < 0 || number > 999999999999) {
            throw std::domain_error("Number must be between 0 and 999,999,999,999");
        }

        if (number < 20) {
            return ones[number];
        }

        if (number < 100) {
            int ten = number / 10;
            int one = number % 10;
            return tens[ten] + (one == 0 ? "" : "-" + ones[one]);
        }

        if (number < 1000) {
            int hundred = number / 100;
            int remainder = number % 100;
            return ones[hundred] + " hundred" + (remainder == 0 ? "" : " " + in_english(remainder));
        }

        if (number < 1000000) {
            int thousand = number / 1000;
            int remainder = number % 1000;
            return in_english(thousand) + " thousand" + (remainder == 0 ? "" : " " + in_english(remainder));
        }

        if (number < 1000000000) {
            int million = number / 1000000;
            int remainder = number % 1000000;
            return in_english(million) + " million" + (remainder == 0 ? "" : " " + in_english(remainder));
        }

        int billion = number / 1000000000;
        int remainder = number % 1000000000;
        return in_english(billion) + " billion" + (remainder == 0 ? "" : " " + in_english(remainder));
    }
} // namespace say