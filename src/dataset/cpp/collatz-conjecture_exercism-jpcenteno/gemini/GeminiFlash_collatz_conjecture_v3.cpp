#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {

    std::int64_t steps(std::int64_t n) {

        if (n < 1) {
            throw std::domain_error("n must be positive");
        }

        std::int64_t i = 0;

        while (n != 1) {
            if ((n & 1) == 0) {
                n >>= 1;
            } else {
                if (n > (std::numeric_limits<std::int64_t>::max() - 1) / 3) {
                    throw std::overflow_error("Potential overflow");
                }
                n = 3 * n + 1;
                if (n < 0) {
                    throw std::overflow_error("Potential overflow");
                }
            }

            i++;
        }

        return i;
    }

}  // namespace collatz_conjecture