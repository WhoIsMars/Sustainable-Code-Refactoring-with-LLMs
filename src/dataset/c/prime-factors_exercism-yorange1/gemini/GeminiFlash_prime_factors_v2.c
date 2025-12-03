#include "prime_factors.h"
#include <math.h>

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS]) {
    size_t index = 0;

    // Handle 2 separately for optimization
    while (n % 2 == 0) {
        factors[index++] = 2;
        n /= 2;
    }

    // Iterate only through odd numbers up to the square root of n
    for (uint64_t candidate = 3; candidate * candidate <= n; candidate += 2) {
        while (n % candidate == 0) {
            factors[index++] = candidate;
            n /= candidate;
        }
    }

    // If n is still greater than 1, it must be a prime number
    if (n > 1) {
        factors[index++] = n;
    }

    return index;
}