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

    constexpr std::array<const char*, 4> scale_names{
        "hundred", "thousand", "million", "billion"
    };

    constexpr std::array<long long, 4> scale_values{
        100, 1000, 1000000, 1000000000
    };

    int largest_named_divisor(const long long number) {
        int divisor = 1;
        for (int i = 0; i < 4; ++i) {
            if (number >= scale_values[i]) {
                divisor = scale_values[i];
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

        int scale_index = 0;
        for (int i = 0; i < 4; ++i) {
            if (scale_values[i] == divisor) {
                scale_index = i;
                break;
            }
        }

        return in_english(quotient) + " " + scale_names[scale_index]
            + padded_english_remainder(remainder, " ");
    }

    std::string in_english_20_to_99(const int number) {
        const auto remainder = number % 10;
        const auto tens_digit = number / 10;

        return std::string(tens[tens_digit]) + padded_english_remainder(remainder, "-");
    }

    std::string in_english(const long long number) {
        if (number >= 1000000000000LL) {
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