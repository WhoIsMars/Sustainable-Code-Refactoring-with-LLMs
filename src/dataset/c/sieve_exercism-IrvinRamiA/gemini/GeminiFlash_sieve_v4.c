#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2) return 0;

    uint32_t primes_counter = 0;
    bool *is_prime = (bool *)malloc((limit + 1) * sizeof(bool));

    if (is_prime == NULL) return 0;

    memset(is_prime, true, (limit + 1) * sizeof(bool));

    is_prime[0] = is_prime[1] = false;

    uint32_t sqrt_limit = (uint32_t)sqrt(limit);

    for (uint32_t i = 2; i <= sqrt_limit; i++)
    {
        if (is_prime[i])
        {
            for (uint32_t j = i * i; j <= limit; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    for (uint32_t i = 2; i <= limit && primes_counter < max_primes; i++)
    {
        if (is_prime[i])
        {
            primes[primes_counter++] = i;
        }
    }

    free(is_prime);
    return primes_counter;
}