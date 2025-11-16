#include "say.h"
#include <unordered_map>
#include <stdexcept>
#include <string>

namespace say {

    const std::unordered_map<int, std::string> english_numbers{
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
        {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},
        {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"},
        {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"},
        {19, "nineteen"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"},
        {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"},
        {90, "ninety"}
    };

    const std::unordered_map<int, std::string> named_place_values{
        {100, "hundred"}, {1'000, "thousand"}, {1'000'000, "million"}, {1'000'000'000, "billion"}
    };

    int largest_named_divisor(const long long number) {
        if (number >= 1'000'000'000) return 1'000'000'000;
        if (number >= 1'000'000) return 1'000'000;
        if (number >= 1'000) return 1'000;
        if (number >= 100) return 100;
        return 1;
    }

    std::string padded_english_remainder(const long long number, const std::string& padding) {
        return number ? padding + in_english(number) : "";
    }

    std::string in_english_100_and_greater(const long long number) {
        const auto divisor = largest_named_divisor(number);
        const auto quotient = number / divisor;
        const auto remainder = number % divisor;
        return in_english(quotient) + " " + named_place_values.at(divisor) +
               padded_english_remainder(remainder, " ");
    }

    std::string in_english_20_to_99(const int number) {
        const auto tens = number / 10 * 10;
        const auto remainder = number % 10;
        return english_numbers.at(tens) + padded_english_remainder(remainder, "-");
    }

    std::string in_english(const long long number) {
        if (number >= 1'000'000'000'000) throw std::domain_error("Numbers greater than or equal to one trillion not supported.");
        if (number < 0) throw std::domain_error("Negative numbers not supported.");
        if (number == 0) return "zero";
        if (number < 20) return english_numbers.at(number);
        if (number < 100) return in_english_20_to_99(number);
        return in_english_100_and_greater(number);
    }

} // namespace say