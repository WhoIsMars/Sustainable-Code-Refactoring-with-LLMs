#include <algorithm>
#include <stdexcept>
#include <vector>

#include "all_your_base.h"

namespace all_your_base {
    std::vector<unsigned int> convert(unsigned int fromBase, const std::vector<unsigned int>& digits, unsigned int toBase) {
        if (fromBase < 2) {
            throw std::invalid_argument("Input base must be 2 or greater.");
        }
        if (toBase < 2) {
            throw std::invalid_argument("Output base must be 2 or greater.");
        }

        // Convert to decimal
        unsigned int decimalNumber = 0;
        for (unsigned int digit : digits) {
            if (digit >= fromBase) {
                throw std::invalid_argument("Input digits cannot be equal or greater than input base.");
            }
            if (__builtin_mul_overflow(decimalNumber, fromBase, &decimalNumber)) {
                throw std::overflow_error("Multiplication overflow during base conversion to decimal.");
            }
            if (__builtin_add_overflow(decimalNumber, digit, &decimalNumber)) {
                throw std::overflow_error("Addition overflow during base conversion to decimal.");
            }
        }

        // Convert from decimal
        std::vector<unsigned int> result;
        if (decimalNumber == 0) {
            result.push_back(0);
            return result;
        }

        while (decimalNumber > 0) {
            result.push_back(decimalNumber % toBase);
            decimalNumber /= toBase;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
} // namespace all_your_base