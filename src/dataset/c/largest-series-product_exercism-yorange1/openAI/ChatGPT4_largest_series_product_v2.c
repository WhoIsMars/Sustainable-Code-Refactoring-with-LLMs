#include "largest_series_product.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

static bool input_handle(const char *digits, int64_t *nums, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return false;
        }

        nums[i] = digits[i] - '0';
    }

    return true;
}

int64_t largest_series_product(const char *digits, size_t span)
{
    assert(digits != NULL);

    size_t len = strlen(digits);
    if (span == 0)
    {
        return 1;
    }
    else if (len == 0 || span > len)
    {
        return -1;
    }

    int64_t max = 0, temp = 1;
    size_t zero_count = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return -1;
        }

        int64_t current_digit = digits[i] - '0';

        if (i < span)
        {
            if (current_digit == 0)
            {
                zero_count++;
            }
            else
            {
                temp *= current_digit;
            }

            if (i == span - 1 && zero_count == 0)
            {
                max = temp;
            }
        }
        else
        {
            int64_t prev_digit = digits[i - span] - '0';

            if (prev_digit == 0)
            {
                zero_count--;
            }
            else
            {
                temp /= prev_digit;
            }

            if (current_digit == 0)
            {
                zero_count++;
            }
            else
            {
                temp *= current_digit;
            }

            if (zero_count == 0 && temp > max)
            {
                max = temp;
            }
        }
    }

    return max;
}