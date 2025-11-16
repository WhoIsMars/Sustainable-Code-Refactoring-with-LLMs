#include "say.h"
#include <array>
#include <stdexcept>

namespace say {

    constexpr std::array<const char*, 20> ones_and_teens{
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", 
        "seventeen", "eighteen", "nineteen"
    };

    constexpr std::array<const char*, 10> tens{
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    struct PlaceValue {
        long long value;
        const char* name;
    };

    constexpr std::array<PlaceValue, 4> place_values{{
        {1'000'000'000, "billion"},
        {1'000'000, "million"},
        {1'000, "thousand"},
        {100, "hundred"}
    }};

    long long largest_named_divisor(const long long number) {
        for (const auto& pv : place_values) {
            if (number >= pv.value) {
                return pv.value;
            }
        }
        return 1;
    }
    
    std::string padded_english_remainder(const long long number, const char* padding) {
        return number == 0 ? "" : std::string(padding) + in_english(number);
    }

    std::string in_english_100_and_greater(const long long number) {
        const auto divisor = largest_named_divisor(number);
        const auto quotient = (number / divisor);
        const auto remainder = (number % divisor);

        const char* place_name = "";
        for (const auto& pv : place_values) {
            if (pv.value == divisor) {
                place_name = pv.name;
                break;
            }
        }

        return in_english(quotient) + " " + place_name + padded_english_remainder(remainder, " ");
    }

    std::string in_english_20_to_99(const int number) {
        const auto remainder = number % 10;
        const auto tens_digit = number / 10;

        return std::string(tens[tens_digit]) + (remainder ? "-" + std::string(ones_and_teens[remainder]) : "");
    }

    std::string in_english(const long long number) {
        if (number >= 1'000'000'000'000) {
            throw std::domain_error("Numbers greater than or equal to one trillion not supported.");
        }

        if (number < 0) { 
            throw std::domain_error("Negative numbers not supported."); 
        }

        if (number == 0) { 
            return "zero"; 
        }

        if (number < 20) { 
            return ones_and_teens[number]; 
        }

        if (number < 100) { 
            return in_english_20_to_99(number); 
        }

        return in_english_100_and_greater(number);
    }

} // namespace say