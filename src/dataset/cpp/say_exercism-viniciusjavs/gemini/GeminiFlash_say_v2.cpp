#include "say.h"

#include <stdexcept>
#include <string>
#include <array>

namespace say {

    std::string in_english(long long number) {
        if (number < 0 || number >= 1000000000000) {
            throw std::domain_error("Number must be between 0 and 999,999,999,999.");
        }

        if (number == 0) {
            return "zero";
        }

        std::string result;

        // Define arrays for numbers up to 19 and tens
        constexpr std::array<const char*, 20> ones = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
        };

        constexpr std::array<const char*, 10> tens = {
            "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
        };

        // Helper function to convert numbers less than 1000
        auto convert_less_than_1000 = [&](long long num) -> std::string {
            std::string res;

            if (num >= 100) {
                res += ones[num / 100];
                res += " hundred";
                num %= 100;
                if (num > 0) {
                    res += " ";
                }
            }

            if (num >= 20) {
                res += tens[num / 10];
                num %= 10;
                if (num > 0) {
                    res += "-";
                }
            }

            if (num > 0) {
                res += ones[num];
            }

            return res;
        };

        // Handle billions
        if (number >= 1000000000) {
            result += convert_less_than_1000(number / 1000000000);
            result += " billion";
            number %= 1000000000;
            if (number > 0) {
                result += " ";
            }
        }

        // Handle millions
        if (number >= 1000000) {
            result += convert_less_than_1000(number / 1000000);
            result += " million";
            number %= 1000000;
            if (number > 0) {
                result += " ";
            }
        }

        // Handle thousands
        if (number >= 1000) {
            result += convert_less_than_1000(number / 1000);
            result += " thousand";
            number %= 1000;
            if (number > 0) {
                result += " ";
            }
        }

        // Handle remaining numbers less than 1000
        result += convert_less_than_1000(number);

        return result;
    }

} // namespace say