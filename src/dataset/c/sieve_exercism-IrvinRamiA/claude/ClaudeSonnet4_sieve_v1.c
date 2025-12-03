#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2 || max_primes == 0) return 0;
    
    uint32_t primes_counter = 0;
    
    // Handle 2 separately to allow odd-only optimization
    if (primes_counter < max_primes) {
        primes[primes_counter++] = 2;
    }
    
    if (limit < 3) return primes_counter;
    
    // Only allocate for odd numbers (3, 5, 7, ...)
    uint32_t odd_limit = (limit - 1) / 2;
    bool *is_prime = (bool *)malloc(odd_limit * sizeof(bool));
    if (!is_prime) return primes_counter;
    
    memset(is_prime, true, odd_limit * sizeof(bool));
    
    // Sieve odd numbers only
    for (uint32_t i = 3; i * i <= limit; i += 2) {
        uint32_t idx = (i - 3) / 2;
        if (is_prime[idx]) {
            for (uint32_t j = i * i; j <= limit; j += 2 * i) {
                uint32_t j_idx = (j - 3) / 2;
                is_prime[j_idx] = false;
            }
        }
    }
    
    // Collect odd primes
    for (uint32_t i = 0; i < odd_limit && primes_counter < max_primes; i++) {
        if (is_prime[i]) {
            primes[primes_counter++] = 2 * i + 3;
        }
    }
    
    free(is_prime);
    return primes_counter;
}