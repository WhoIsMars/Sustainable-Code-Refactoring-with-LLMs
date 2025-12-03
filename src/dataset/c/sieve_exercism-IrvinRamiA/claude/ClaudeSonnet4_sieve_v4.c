#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2 || max_primes == 0) return 0;
    
    uint32_t primes_counter = 0;
    size_t sieve_size = (limit + 1) / 8 + 1;
    unsigned char *is_prime = (unsigned char *)malloc(sieve_size);
    
    memset(is_prime, 0xFF, sieve_size);
    
    is_prime[0] &= 0xFC;
    
    uint32_t sqrt_limit = 1;
    while (sqrt_limit * sqrt_limit <= limit) sqrt_limit++;
    sqrt_limit--;
    
    for (uint32_t i = 2; i <= sqrt_limit; i++) {
        if (is_prime[i >> 3] & (1 << (i & 7))) {
            for (uint32_t j = i * i; j <= limit; j += i) {
                is_prime[j >> 3] &= ~(1 << (j & 7));
            }
        }
    }
    
    for (uint32_t i = 2; i <= limit && primes_counter < max_primes; i++) {
        if (is_prime[i >> 3] & (1 << (i & 7))) {
            primes[primes_counter++] = i;
        }
    }
    
    free(is_prime);
    return primes_counter;
}