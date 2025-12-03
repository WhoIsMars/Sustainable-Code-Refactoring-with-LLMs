#include "sieve.h"

#include <stdbool.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit <= 1)
    {
        return 0;
    }

    // Use bit array to reduce memory by 8x
    size_t array_size = (limit + 1 + 7) / 8;
    uint8_t primes_flags[array_size];
    memset(primes_flags, 0xFF, array_size);

    // Clear bits for 0 and 1
    primes_flags[0] &= ~0x03;

    uint32_t count = 0;
    
    // Handle 2 separately to allow odd-only optimization
    if (limit >= 2 && count < max_primes)
    {
        primes[count++] = 2;
        // Mark all even numbers as composite
        for (size_t j = 4; j <= limit; j += 2)
        {
            primes_flags[j / 8] &= ~(1 << (j % 8));
        }
    }

    // Only check odd numbers from 3 onwards
    for (size_t i = 3; i <= limit && count < max_primes; i += 2)
    {
        if (primes_flags[i / 8] & (1 << (i % 8)))
        {
            primes[count++] = i;
            
            // Start marking from i*i and only mark odd multiples
            if (i <= 65535) // Prevent overflow for i*i
            {
                for (size_t j = i * i; j <= limit; j += 2 * i)
                {
                    primes_flags[j / 8] &= ~(1 << (j % 8));
                }
            }
        }
    }

    return count;
}