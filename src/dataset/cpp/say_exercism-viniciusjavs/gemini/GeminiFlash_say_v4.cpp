#include "say.h"

#include <stdexcept>
#include <string>
#include <array>

namespace say {

    std::string in_english(long long number) {
        if (number < 0 || number > 999999999999) {
            throw std::domain_error("Number must be between 0 and 999,999,999,999.");
        }

        if (number == 0) {
            return "zero";
        }

        std::string result;

        const std::array<std::string, 20> ones = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
        };

        const std::array<std::string, 10> tens = {
            "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
        };

        const std::array<std::string, 4> thousands = {
            "", "thousand", "million", "billion"
        };

        auto convert_chunk = [&](long long n) -> std::string {
            std::string chunk_result;

            if (n >= 100) {
                chunk_result += ones[n / 100] + " hundred";
                n %= 100;
                if (n > 0) {
                    chunk_result += " ";
                }
            }

            if (n >= 20) {
                chunk_result += tens[n / 10];
                n %= 10;
                if (n > 0) {
                    chunk_result += "-";
                }
            }

            if (n > 0) {
                chunk_result += ones[n];
            }

            return chunk_result;
        };

        for (int i = 0; number > 0; ++i) {
            long long chunk = number % 1000;
            if (chunk > 0) {
                std::string chunk_str = convert_chunk(chunk);
                if (!result.empty()) {
                    chunk_str += " ";
                }
                chunk_str += thousands[i];
                if (!result.empty()) {
                    chunk_str += ", ";
                }
                result.insert(0, chunk_str);
            }
            number /= 1000;
        }

        // Remove trailing ", " if it exists
        if (result.size() > 2 && result.substr(result.size() - 2) == ", ") {
            result.resize(result.size() - 2);
        }

        return result;
    }

} // namespace say