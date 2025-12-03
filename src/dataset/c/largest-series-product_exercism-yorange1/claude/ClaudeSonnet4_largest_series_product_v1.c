#include "largest_series_product.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int64_t largest_series_product(char *digits, size_t span)
{
    assert(digits != NULL);

    size_t len = strlen(digits);

    if (span == 0)
    {
        return 1;
    }
    else if ((len == 0 && span > 0) || span > len)
    {
        return -1;
    }

    // Validate input and find first valid window
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }
    }

    int64_t max = 0;
    
    for (size_t i = 0; i <= len - span; i++)
    {
        int64_t product = 1;
        bool has_zero = false;
        
        for (size_t j = 0; j < span; j++)
        {
            int64_t digit = digits[i + j] - '0';
            if (digit == 0)
            {
                has_zero = true;
                break;
            }
            product *= digit;
        }
        
        if (!has_zero && product > max)
        {
            max = product;
        }
        
        // Skip ahead if we hit a zero
        if (has_zero)
        {
            while (i < len && digits[i] != '0')
            {
                i++;
            }
        }
    }

    return max;
}