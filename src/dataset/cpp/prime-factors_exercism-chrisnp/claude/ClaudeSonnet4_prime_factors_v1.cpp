#include "prime_factors.h"

std::vector<int> prime_factors::of(uint64_t num) {
    std::vector<int> factors;
    factors.reserve(32); // Reserve space to avoid reallocations
    
    // Handle factor 2 separately
    while (num % 2 == 0) {
        factors.push_back(2);
        num /= 2;
    }
    
    // Check odd factors only up to sqrt(num)
    for (uint64_t factor = 3; factor * factor <= num; factor += 2) {
        while (num % factor == 0) {
            factors.push_back(static_cast<int>(factor));
            num /= factor;
        }
    }
    
    // If num > 1, then it's a prime factor
    if (num > 1) {
        factors.push_back(static_cast<int>(num));
    }
    
    return factors;
}