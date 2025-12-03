#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2) return 0;
    
    uint32_t primes_counter = 0;
    bool *is_prime = (bool *)malloc((limit + 1) * sizeof(bool));
    
    // Initialize array - set all to true except 0 and 1
    memset(is_prime, true, (limit + 1) * sizeof(bool));
    is_prime[0] = is_prime[1] = false;

    // Handle 2 separately to allow odd-only optimization
    if (primes_counter < max_primes) {
        primes[primes_counter++] = 2;
    }
    
    // Mark even numbers > 2 as composite
    for (uint32_t i = 4; i <= limit; i += 2) {
        is_prime[i] = false;
    }

    // Sieve odd numbers only
    for (uint32_t i = 3; i * i <= limit; i += 2) {
        if (is_prime[i]) {
            // Start from i*i and increment by 2*i to hit only odd multiples
            for (uint32_t j = i * i; j <= limit; j += 2 * i) {
                is_prime[j] = false;
            }
        }
    }

    // Collect odd primes
    for (uint32_t i = 3; i <= limit && primes_counter < max_primes; i += 2) {
        if (is_prime[i]) {
            primes[primes_counter++] = i;
        }
    }

    free(is_prime);
    return primes_counter;
}