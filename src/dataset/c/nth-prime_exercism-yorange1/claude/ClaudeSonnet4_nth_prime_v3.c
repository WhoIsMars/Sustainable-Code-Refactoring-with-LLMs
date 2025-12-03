#include "nth_prime.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_prime(uint32_t n)
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    uint32_t limit = (uint32_t)sqrt(n);
    for (uint32_t i = 5; i <= limit; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    
    return true;
}

uint32_t nth(uint32_t n)
{
    if (n == 1) return 2;
    
    size_t count = 1;
    uint32_t candidate = 3;
    
    while (count < n)
    {
        if (is_prime(candidate))
        {
            count++;
        }
        candidate += 2;
    }
    
    return candidate - 2;
}