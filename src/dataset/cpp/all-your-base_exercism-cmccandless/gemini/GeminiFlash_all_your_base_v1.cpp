#include <algorithm>
#include <stdexcept>
#include <vector>

#include "all_your_base.h"

namespace all_your_base {
    unsigned int toDecimalNumber(unsigned int fromBase, const std::vector<unsigned int>& digits) {
        if (fromBase < 2) {
            throw std::invalid_argument("Input base must be 2 or greater.");
        }

        unsigned int num = 0;
        for (unsigned int digit : digits) {
            if (digit >= fromBase) {
                throw std::invalid_argument("Input digits cannot be equal or greater than input base.");
            }
            if (__builtin_mul_overflow(num, fromBase, &num)) {
                throw std::overflow_error("Multiplication overflow");
            }
            if (__builtin_add_overflow(num, digit, &num)) {
                throw std::overflow_error("Addition overflow");
            }
        }
        return num;
    }

    std::vector<unsigned int> fromDecimalNumber(unsigned int decimalNumber, unsigned int toBase) {
        if (toBase < 2) {
            throw std::invalid_argument("Output base must be 2 or greater.");
        }

        if (decimalNumber == 0) {
            return {0};
        }

        std::vector<unsigned int> digits;
        unsigned int rem;
        while (decimalNumber > 0) {
            rem = decimalNumber % toBase;
            digits.push_back(rem);
            decimalNumber /= toBase;
        }
        std::reverse(digits.begin(), digits.end());
        return digits;
    }

    std::vector<unsigned int> convert(unsigned int fromBase, const std::vector<unsigned int>& digits, unsigned int toBase) {
        if (fromBase < 2) {
            throw std::invalid_argument("Input base must be 2 or greater.");
        }
        if (toBase < 2) {
            throw std::invalid_argument("Output base must be 2 or greater.");
        }

        if (digits.empty() && fromBase != 1) {
            return {0};
        }

        return fromDecimalNumber(toDecimalNumber(fromBase, digits), toBase);
    }
} // namespace all_your_base