#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS])
{
    size_t index = 0;

    while (n % 2 == 0) {
        factors[index++] = 2;
        n /= 2;
    }

    for (uint64_t candidate = 3; candidate * candidate <= n; candidate += 2)
    {
        while (n % candidate == 0) {
            factors[index++] = candidate;
            n /= candidate;
        }
    }
    
    if (n > 1) {
        factors[index++] = n;
    }
    
    return index;
}