#include "prime_factors.h"

std::vector<int> prime_factors::of(uint64_t num) {
    std::vector<int> factors;
    while (num % 2 == 0) {
        factors.push_back(2);
        num /= 2;
    }
    for (uint64_t factor = 3; factor * factor <= num; factor += 2) {
        while (num % factor == 0) {
            factors.push_back(factor);
            num /= factor;
        }
    }
    if (num > 1) {
        factors.push_back(num);
    }
    return factors;
}