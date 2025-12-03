#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS])
{
    size_t index = 0;

    // Handle factor 2 separately to allow skipping even numbers
    while (n % 2 == 0) {
        factors[index++] = 2;
        n /= 2;
    }

    // Check odd numbers only, up to sqrt(n)
    for (uint64_t candidate = 3; candidate * candidate <= n; candidate += 2)
    {
        while (n % candidate == 0) {
            factors[index++] = candidate;
            n /= candidate;
        }
    }
    
    // If n is still > 1, then it's a prime factor
    if (n > 1) {
        factors[index++] = n;
    }
    
    return index;
}