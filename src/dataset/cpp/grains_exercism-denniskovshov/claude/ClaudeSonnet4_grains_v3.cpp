#include <cmath>
#include <stdexcept>
#include "grains.h"

namespace grains {
    constexpr short min_square_num = 1;
    constexpr short max_square_num = 64;
    constexpr unsigned long long max_total = 18446744073709551615ULL;
    
    auto square_func = square_bit_shift;

    unsigned long long square(short square_num) {
        if (square_num < min_square_num || square_num > max_square_num) {
            throw std::domain_error("Square number must be >= 1 and <= 64");
        }
        return 1ULL << (square_num - 1);
    }

    unsigned long long square_bit_shift(short square_num) {
        return 1ULL << (square_num - 1);
    }

    unsigned long long square_std_pow(short square_num) {
        return 1ULL << (square_num - 1);
    }

    unsigned long long total() {
        return max_total;
    }

    void validate(short square_num) {
        if (square_num < min_square_num || square_num > max_square_num) {
            throw std::domain_error("Square number must be >= 1 and <= 64");
        }
    }
}