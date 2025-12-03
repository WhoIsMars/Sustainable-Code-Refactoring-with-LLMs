#include "sieve.h"
#include <stdbool.h>
#include <stdlib.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit < 2 || max_primes == 0)
        return 0;

    uint32_t primes_counter = 0;
    bool *is_prime = (bool *)calloc(limit + 1, sizeof(bool));

    if (!is_prime)
        return 0;

    for (uint32_t i = 2; i <= limit; i++)
        is_prime[i] = true;

    for (uint32_t i = 2; i * i <= limit; i++)
    {
        if (is_prime[i])
        {
            for (uint32_t j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }

    for (uint32_t i = 2; i <= limit && primes_counter < max_primes; i++)
    {
        if (is_prime[i])
            primes[primes_counter++] = i;
    }

    free(is_prime);
    return primes_counter;
}