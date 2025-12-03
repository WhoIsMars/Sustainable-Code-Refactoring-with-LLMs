#include "say.h"

#include <stdexcept>
#include <sstream>
#include <unordered_map>

namespace say {

    std::string in_english(long long number) {
        if (number < 0 || number >= 1000000000000) {
            throw std::domain_error("Number must be between 0 and 999,999,999,999.");
        }

        if (number == 0) {
            return "zero";
        }

        std::unordered_map<long long, std::string> below_20 = {
            {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
            {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},
            {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"},
            {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"},
            {19, "nineteen"}
        };

        std::unordered_map<long long, std::string> tens = {
            {20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"},
            {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}
        };

        std::stringstream result;

        if (number >= 1000000000) {
            result << in_english(number / 1000000000) << " billion";
            number %= 1000000000;
            if (number > 0) {
                result << " ";
            }
        }

        if (number >= 1000000) {
            result << in_english(number / 1000000) << " million";
            number %= 1000000;
            if (number > 0) {
                result << " ";
            }
        }

        if (number >= 1000) {
            result << in_english(number / 1000) << " thousand";
            number %= 1000;
            if (number > 0) {
                result << " ";
            }
        }

        if (number >= 100) {
            result << in_english(number / 100) << " hundred";
            number %= 100;
            if (number > 0) {
                result << " ";
            }
        }

        if (number >= 20) {
            result << tens[number / 10 * 10];
            number %= 10;
            if (number > 0) {
                result << "-";
            }
        }

        if (number > 0) {
            result << below_20[number];
        }

        return result.str();
    }

} // namespace say