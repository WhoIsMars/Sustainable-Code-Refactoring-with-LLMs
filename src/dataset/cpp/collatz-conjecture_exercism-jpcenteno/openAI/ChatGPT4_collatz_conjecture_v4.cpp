#include "collatz_conjecture.h"

#include <stdexcept>

namespace collatz_conjecture {

    std::int64_t steps(std::int64_t n) {
        if (n < 1) {
            throw std::domain_error("n must be positive");
        }

        std::int64_t i = 0;
        while (n != 1) {
            n = (n % 2 == 0) ? (n / 2) : (3 * n + 1);
            ++i;
        }

        return i;
    }

}  // namespace collatz_conjecture