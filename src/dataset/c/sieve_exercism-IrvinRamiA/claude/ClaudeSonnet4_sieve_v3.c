#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2 || max_primes == 0) return 0;
    
    uint32_t primes_counter = 0;
    
    if (limit >= 2 && primes_counter < max_primes) {
        primes[primes_counter++] = 2;
    }
    
    if (limit < 3) return primes_counter;
    
    uint32_t odd_limit = (limit - 1) / 2;
    bool *is_prime = (bool *)malloc(odd_limit * sizeof(bool));
    if (!is_prime) return primes_counter;
    
    memset(is_prime, true, odd_limit * sizeof(bool));
    
    for (uint32_t i = 1; (2 * i + 1) * (2 * i + 1) <= limit; i++) {
        if (is_prime[i]) {
            uint32_t prime = 2 * i + 1;
            for (uint32_t j = (prime * prime - 1) / 2; j < odd_limit; j += prime) {
                is_prime[j] = false;
            }
        }
    }
    
    for (uint32_t i = 1; i < odd_limit && primes_counter < max_primes; i++) {
        if (is_prime[i]) {
            primes[primes_counter++] = 2 * i + 1;
        }
    }
    
    free(is_prime);
    return primes_counter;
}