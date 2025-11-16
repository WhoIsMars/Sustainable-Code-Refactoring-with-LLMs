#include "prime_factors.h"

std::vector<int> prime_factors::of(uint64_t num) {

    std::vector<int> factors {};
    uint64_t factor {2};

    while (factor * factor <= num) {
        while (num % factor == 0) {
            factors.push_back(factor);
            num /= factor;
        }
        ++factor;
    }
    if (num > 1) {
        factors.push_back(num);
    }
    return factors;
}