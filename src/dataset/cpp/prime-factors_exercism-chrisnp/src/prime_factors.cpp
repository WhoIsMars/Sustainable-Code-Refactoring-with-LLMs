#include "prime_factors.h"

std::vector<int> prime_factors::of(uint64_t num) {

    std::vector<int> factors {};
    uint64_t factor {2};

    while (factor <= num) {
        if (num % factor == 0) {
            factors.insert(factors.end(), factor);
            num /= factor;
        } else {
            ++factor;
        }
    }
    return factors;
}
