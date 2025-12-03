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

    // Validate input and calculate first window product
    int64_t current_product = 1;
    for (size_t i = 0; i < span; i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }
        current_product *= (digits[i] - '0');
    }

    int64_t max_product = current_product;

    // Sliding window approach
    for (size_t i = span; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }

        int64_t old_digit = digits[i - span] - '0';
        int64_t new_digit = digits[i] - '0';

        if (old_digit == 0)
        {
            // Recalculate product when removing zero
            current_product = 1;
            for (size_t j = i - span + 1; j <= i; j++)
            {
                current_product *= (digits[j] - '0');
            }
        }
        else
        {
            current_product = (current_product / old_digit) * new_digit;
        }

        if (current_product > max_product)
        {
            max_product = current_product;
        }
    }

    return max_product;
}