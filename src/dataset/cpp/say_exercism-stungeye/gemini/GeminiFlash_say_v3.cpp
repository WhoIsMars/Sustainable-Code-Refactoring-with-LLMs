#include "say.h"
#include <array>
#include <stdexcept>
#include <string>

namespace say {

    constexpr std::array<std::pair<int, const char*>, 27> english_numbers = {
        std::make_pair(1, "one"),
        std::make_pair(2, "two"),
        std::make_pair(3, "three"),
        std::make_pair(4, "four"),
        std::make_pair(5, "five"),
        std::make_pair(6, "six"),
        std::make_pair(7, "seven"),
        std::make_pair(8, "eight"),
        std::make_pair(9, "nine"),
        std::make_pair(10, "ten"),
        std::make_pair(11, "eleven"),
        std::make_pair(12, "twelve"),
        std::make_pair(13, "thirteen"),
        std::make_pair(14, "fourteen"),
        std::make_pair(15, "fifteen"),
        std::make_pair(16, "sixteen"),
        std::make_pair(17, "seventeen"),
        std::make_pair(18, "eighteen"),
        std::make_pair(19, "nineteen"),
        std::make_pair(20, "twenty"),
        std::make_pair(30, "thirty"),
        std::make_pair(40, "forty"),
        std::make_pair(50, "fifty"),
        std::make_pair(60, "sixty"),
        std::make_pair(70, "seventy"),
        std::make_pair(80, "eighty"),
        std::make_pair(90, "ninety")
    };

    constexpr std::array<std::pair<int, const char*>, 4> named_place_values = {
        std::make_pair(100, "hundred"),
        std::make_pair(1'000, "thousand"),
        std::make_pair(1'000'000, "million"),
        std::make_pair(1'000'000'000, "billion")
    };

    int largest_named_divisor(const long long number) {
        int divisor = 1;
        for (const auto& [key, value] : named_place_values) {
            if (number >= key) {
                divisor = key;
            }
        }
        return divisor;
    }

    std::string padded_english_remainder(const long long number, const char* padding) {
        return number == 0 ? "" : std::string(padding) + in_english(number);
    }

    std::string in_english_100_and_greater(const long long number) {
        const auto divisor = largest_named_divisor(number);
        const auto quotient = (number / divisor);
        const auto remainder = (number % divisor);

        return in_english(quotient) + " " + named_place_values[std::distance(named_place_values.begin(), std::find_if(named_place_values.begin(), named_place_values.end(), [&divisor](const auto& element){ return element.first == divisor; }))].second
            + padded_english_remainder(remainder, " ");
    }

    std::string in_english_20_to_99(const int number) {
        const auto remainder = number % 10;
        const auto tens = number - remainder;

        auto it = std::find_if(english_numbers.begin(), english_numbers.end(), [&tens](const auto& element){ return element.first == tens; });

        return it->second + padded_english_remainder(remainder, "-");
    }

    std::string in_english(const long long number) {
        if (number >= 1'000'000'000'000) {
            throw std::domain_error("Numbers greater than or equal to one trillion not supported.");
        }

        if (number < 0) { throw std::domain_error("Negative numbers not supported."); }

        if (number == 0) { return "zero"; }

        if (number < 20) {
            auto it = std::find_if(english_numbers.begin(), english_numbers.end(), [&number](const auto& element){ return element.first == number; });
            return it->second;
        }

        if (number < 100) { return in_english_20_to_99(number); }

        return in_english_100_and_greater(number);
    }

} // namespace say