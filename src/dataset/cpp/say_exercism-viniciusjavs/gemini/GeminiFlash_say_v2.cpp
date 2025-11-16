#include "say.h"

#include <stdexcept>
#include <string>
#include <sstream>

namespace say {

    const std::string ones[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const std::string teens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const std::string tens[10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    std::string in_english(long long number) {
        if (number < 0 || number > 999999999999) {
            throw std::domain_error("Number must be between 0 and 999,999,999,999.");
        }

        if (number == 0) {
            return "zero";
        }

        std::stringstream result;

        if (number >= 1000000000) {
            result << in_english(number / 1000000000) << " billion";
            number %= 1000000000;
            if (number > 0) result << " ";
        }

        if (number >= 1000000) {
            result << in_english(number / 1000000) << " million";
            number %= 1000000;
            if (number > 0) result << " ";
        }

        if (number >= 1000) {
            result << in_english(number / 1000) << " thousand";
            number %= 1000;
            if (number > 0) result << " ";
        }

        if (number >= 100) {
            result << ones[number / 100] << " hundred";
            number %= 100;
            if (number > 0) result << " ";
        }

        if (number >= 20) {
            result << tens[number / 10];
            number %= 10;
            if (number > 0) result << "-";
        } else if (number >= 10) {
            result << teens[number - 10];
            number = 0;
        }

        if (number > 0) {
            result << ones[number];
        }

        return result.str();
    }

} // namespace say