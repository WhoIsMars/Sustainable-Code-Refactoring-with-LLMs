#include "nth_prime.h"
#include <stdbool.h>

#define U32_MAX_VALUE 4294967295

static bool is_prime(uint32_t number)
{
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;
    
    for (uint32_t i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }
    
    return true;
}

uint32_t nth(uint32_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 2;
    
    uint32_t primes_counter = 1;
    uint32_t candidate = 3;
    
    while (primes_counter < n)
    {
        if (is_prime(candidate))
        {
            primes_counter++;
            if (primes_counter == n)
                return candidate;
        }
        candidate += 2;
    }
    
    return candidate;
}