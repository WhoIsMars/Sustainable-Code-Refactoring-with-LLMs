#include "sieve.h"

#include <stdbool.h>
#include <string.h>
#include <math.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit <= 1)
    {
        return 0;
    }

    uint8_t *primes_flags = calloc(limit + 1, sizeof(uint8_t));
    if (!primes_flags)
    {
        return 0;
    }

    memset(primes_flags, 1, limit + 1);

    primes_flags[0] = 0;
    primes_flags[1] = 0;

    uint32_t count = 0;
    uint32_t sqrt_limit = (uint32_t)sqrt(limit);

    for (uint32_t i = 2; i <= sqrt_limit; i++)
    {
        if (primes_flags[i])
        {
            for (uint32_t j = i * i; j <= limit; j += i)
            {
                primes_flags[j] = 0;
            }
        }
    }

    for (uint32_t i = 2; i <= limit && count < max_primes; i++)
    {
        if (primes_flags[i])
        {
            primes[count++] = i;
        }
    }

    free(primes_flags);
    return count;
}