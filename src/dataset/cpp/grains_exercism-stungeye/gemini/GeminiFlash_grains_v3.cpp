#include "grains.h"
#include <stdexcept>

namespace grains {
    unsigned long long square(int n)
    {
        if (n <= 0 || n > 64) {
            throw std::domain_error("square must be between 1 and 64");
        }
        return 1ULL << (n - 1);
    }

    unsigned long long total() {
        return ~0ULL;
    }
}  // namespace grains