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

    int64_t max = 0;
    int64_t current_product = 1;
    size_t zero_count = 0;
    
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }
        
        int64_t digit = digits[i] - '0';
        
        if (i < span)
        {
            current_product *= digit;
            if (digit == 0) zero_count++;
        }
        else
        {
            int64_t old_digit = digits[i - span] - '0';
            if (old_digit == 0)
            {
                zero_count--;
                current_product = 1;
                for (size_t j = i - span + 1; j <= i; j++)
                {
                    current_product *= (digits[j] - '0');
                }
            }
            else
            {
                current_product = current_product / old_digit * digit;
            }
            
            if (digit == 0) zero_count++;
        }
        
        if (i >= span - 1)
        {
            if (zero_count == 0 && current_product > max)
            {
                max = current_product;
            }
        }
    }

    return max;
}