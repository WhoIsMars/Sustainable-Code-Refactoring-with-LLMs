#include "prime_factors.h"

std::vector<int> prime_factors::of(uint64_t num) {
    std::vector<int> factors;
    
    if (num <= 1) return factors;
    
    factors.reserve(32);
    
    while (num % 2 == 0) {
        factors.push_back(2);
        num /= 2;
    }
    
    for (uint64_t factor = 3; factor * factor <= num; factor += 2) {
        while (num % factor == 0) {
            factors.push_back(static_cast<int>(factor));
            num /= factor;
        }
    }
    
    if (num > 2) {
        factors.push_back(static_cast<int>(num));
    }
    
    return factors;
}