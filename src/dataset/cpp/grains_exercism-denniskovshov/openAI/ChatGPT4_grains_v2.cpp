#include <stdexcept>
#include "grains.h"

namespace grains {
    constexpr short min_square_num = 1;
    constexpr short max_square_num = 64;

    unsigned long long square(short square_num) {
        if (square_num < min_square_num || square_num > max_square_num) {
            throw std::domain_error("Square number must be >= " + std::to_string(min_square_num) + " and <= " + std::to_string(max_square_num));
        }
        return 1ULL << (square_num - 1);
    }

    unsigned long long total() {
        return (1ULL << max_square_num) - 1;
    }
}  // namespace grains