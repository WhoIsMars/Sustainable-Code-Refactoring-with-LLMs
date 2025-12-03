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

        // Early exit for empty input
        if (digits.empty()) {
            return {0};
        }

        unsigned int decimalNumber = 0;
        for (unsigned int digit : digits) {
            if (digit >= fromBase) {
                throw std::invalid_argument("Input digits cannot be equal or greater than input base.");
            }
            if (decimalNumber > (UINT_MAX / fromBase)) {
                throw std::overflow_error("Overflow during base conversion to decimal.");
            }
            decimalNumber = decimalNumber * fromBase + digit;
        }

        if (decimalNumber == 0) {
            return {0};
        }

        std::vector<unsigned int> result;
        while (decimalNumber > 0) {
            result.push_back(decimalNumber % toBase);
            decimalNumber /= toBase;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
} // namespace all_your_base