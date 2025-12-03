#include "nth_prime.h"
#include <stdbool.h>
#include <math.h>

uint32_t nth(uint32_t n) {
    if (n == 0) {
        return 0;
    }

    // Estimate the upper bound for the nth prime number.  This avoids unnecessary iterations.
    // A simple approximation is n * log(n) but we add some extra margin.
    uint32_t upper_bound = (n < 6) ? 15 : (uint32_t)(n * (log(n) + log(log(n))));
    if (upper_bound < 0) return 0; // Handle overflow

    uint32_t *primes = (uint32_t*)malloc(n * sizeof(uint32_t));
    if (!primes) return 0; // Handle allocation failure

    uint32_t count = 0;
    for (uint32_t i = 2; i <= upper_bound; ++i) {
        bool is_prime = true;
        for (uint32_t j = 0; j < count; ++j) {
            if (i % primes[j] == 0) {
                is_prime = false;
                break;
            }
            if (primes[j] * primes[j] > i) break; // Optimization: only check up to sqrt(i)
        }
        if (is_prime) {
            primes[count++] = i;
            if (count == n) {
                uint32_t result = primes[n - 1];
                free(primes);
                return result;
            }
        }
    }

    free(primes);
    return 0; // Should not reach here if the upper bound is sufficient.  Return 0 to indicate error.
}