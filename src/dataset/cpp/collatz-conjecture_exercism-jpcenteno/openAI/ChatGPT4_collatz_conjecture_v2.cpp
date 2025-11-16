#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {

    std::int64_t steps(std::int64_t n) {
        if (n < 1) {
            throw std::domain_error("n must be positive");
        }

        std::int64_t i = 0;

        while (n != 1) {
            if (n & 1) { // Check if n is odd
                n = 3 * n + 1;
            } else {
                n >>= 1; // Use bitwise shift for division by 2
            }
            ++i;
        }

        return i;
    }

}  // namespace collatz_conjecture