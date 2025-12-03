#include "sieve.h"

#include <stdbool.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit <= 1)
    {
        return 0;
    }

    if (limit == 2)
    {
        if (max_primes > 0)
        {
            primes[0] = 2;
            return 1;
        }
        return 0;
    }

    size_t odd_limit = (limit - 1) / 2;
    uint8_t *primes_flags = calloc(odd_limit + 1, sizeof(uint8_t));
    if (!primes_flags)
    {
        return 0;
    }

    uint32_t count = 0;
    if (max_primes > 0)
    {
        primes[count++] = 2;
    }

    for (size_t i = 1; i <= odd_limit && count < max_primes; i++)
    {
        if (primes_flags[i] == 0)
        {
            uint32_t prime = 2 * i + 1;
            primes[count++] = prime;

            if (prime <= 46340)
            {
                size_t start = (prime * prime - 1) / 2;
                for (size_t j = start; j <= odd_limit; j += prime)
                {
                    primes_flags[j] = 1;
                }
            }
        }
    }

    free(primes_flags);
    return count;
}