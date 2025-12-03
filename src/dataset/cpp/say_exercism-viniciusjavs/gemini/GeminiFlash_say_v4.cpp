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

        for (int i = 0; number > 0; ++i) {
            long long chunk = number % 1000;
            number /= 1000;

            if (chunk != 0) {
                std::string chunk_str;

                int hundred = chunk / 100;
                if (hundred > 0) {
                    chunk_str += ones[hundred] + " hundred";
                    chunk %= 100;
                    if (chunk > 0) {
                        chunk_str += " ";
                    }
                }

                if (chunk < 20) {
                    chunk_str += ones[chunk];
                } else {
                    int ten = chunk / 10;
                    chunk_str += tens[ten];
                    chunk %= 10;
                    if (chunk > 0) {
                        chunk_str += "-" + ones[chunk];
                    }
                }

                if (i > 0) {
                    chunk_str += " " + thousands[i];
                }

                if (!result.empty()) {
                    chunk_str += " " + result;
                }

                result = chunk_str;
            }
        }

        return result;
    }

} // namespace say