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

    // Use bit array to reduce memory usage by 8x
    size_t array_size = (limit + 1 + 7) / 8;
    uint8_t primes_flags[array_size];
    memset(primes_flags, 0xFF, array_size);

    // Clear bits for 0 and 1
    primes_flags[0] &= ~0x03;

    uint32_t count = 0;
    
    // Handle 2 separately
    if (max_primes > 0)
    {
        primes[count++] = 2;
    }

    // Only check odd numbers starting from 3
    for (uint32_t i = 3; i <= limit && count < max_primes; i += 2)
    {
        uint32_t byte_idx = i / 8;
        uint32_t bit_idx = i % 8;
        
        if (primes_flags[byte_idx] & (1 << bit_idx))
        {
            primes[count++] = i;
            
            // Start marking from i*i, skip even multiples
            for (uint32_t j = i * i; j <= limit; j += 2 * i)
            {
                uint32_t j_byte_idx = j / 8;
                uint32_t j_bit_idx = j % 8;
                primes_flags[j_byte_idx] &= ~(1 << j_bit_idx);
            }
        }
    }

    return count;
}