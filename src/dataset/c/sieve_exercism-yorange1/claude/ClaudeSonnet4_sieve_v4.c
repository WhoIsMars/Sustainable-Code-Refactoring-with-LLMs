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

    size_t odd_count = (limit - 1) / 2;
    uint8_t *primes_flags = calloc(odd_count, sizeof(uint8_t));
    if (!primes_flags)
    {
        return 0;
    }

    uint32_t count = 0;
    if (max_primes > 0)
    {
        primes[count++] = 2;
    }

    uint32_t sqrt_limit = 1;
    while (sqrt_limit * sqrt_limit <= limit)
    {
        sqrt_limit++;
    }
    sqrt_limit--;

    for (uint32_t i = 3; i <= sqrt_limit && count < max_primes; i += 2)
    {
        size_t idx = (i - 3) / 2;
        if (primes_flags[idx] == 0)
        {
            primes[count++] = i;
            
            for (uint32_t j = i * i; j <= limit; j += 2 * i)
            {
                size_t mark_idx = (j - 3) / 2;
                primes_flags[mark_idx] = 1;
            }
        }
    }

    for (uint32_t i = (sqrt_limit % 2 == 0) ? sqrt_limit + 1 : sqrt_limit + 2; 
         i <= limit && count < max_primes; i += 2)
    {
        size_t idx = (i - 3) / 2;
        if (primes_flags[idx] == 0)
        {
            primes[count++] = i;
        }
    }

    free(primes_flags);
    return count;
}