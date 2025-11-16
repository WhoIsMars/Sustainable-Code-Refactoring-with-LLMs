#include "say.h"
#include <array>
#include <stdexcept>
#include <string>

namespace say {

    const std::array<std::pair<int, std::string>, 27> english_numbers{{
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"},
        {10, "ten"},
        {11, "eleven"},
        {12, "twelve"},
        {13, "thirteen"},
        {14, "fourteen"},
        {15, "fifteen"},
        {16, "sixteen"},
        {17, "seventeen"},
        {18, "eighteen"},
        {19, "nineteen"},
        {20, "twenty"},
        {30, "thirty"},
        {40, "forty"},
        {50, "fifty"},
        {60, "sixty"},
        {70, "seventy"},
        {80, "eighty"},
        {90, "ninety"},
    }};

    const std::array<std::pair<int, std::string>, 4> named_place_values{{
        {100, "hundred"},
        {1'000, "thousand"},
        {1'000'000, "million"},
        {1'000'000'000, "billion"}
    }};

   int largest_named_divisor(const long long number) {
        int divisor = 1;
        for (const auto& pair : named_place_values) {
            if (number >= pair.first) {
                divisor = pair.first;
            }
        }
        return divisor;
    }
    
    std::string padded_english_remainder(const long long number, const std::string& padding) {
        return number == 0 ? "" : padding + in_english(number);
    }

    std::string in_english_100_and_greater(const long long number) {
        const auto divisor = largest_named_divisor(number);
        const auto quotient = (number / divisor);
        const auto remainder = (number % divisor);

        std::string result = in_english(quotient) + " " + [&divisor]() -> std::string {
            for (const auto& pair : named_place_values) {
                if (pair.first == divisor) {
                    return pair.second;
                }
            }
            return ""; // Should never happen
        }();

        result += padded_english_remainder(remainder, " ");
        return result;
    }

    std::string in_english_20_to_99(const int number) {
        const auto remainder = number % 10;
        const auto tens = number - remainder;

        std::string result;
        for (const auto& pair : english_numbers) {
            if (pair.first == tens) {
                result = pair.second;
                break;
            }
        }
        result += padded_english_remainder(remainder, "-");
        return result;
    }

    std::string in_english(const long long number) {
        if (number >= 1'000'000'000'000) {
            throw std::domain_error("Numbers greater than or equal to one trillion not supported.");
        }

        if (number < 0) { throw std::domain_error("Negative numbers not supported."); }

        if (number == 0) { return "zero"; }

        if (number < 20) {
            for (const auto& pair : english_numbers) {
                if (pair.first == number) {
                    return pair.second;
                }
            }
        }

        if (number < 100) { return in_english_20_to_99(number); }

        return in_english_100_and_greater(number);
    }

} // namespace say