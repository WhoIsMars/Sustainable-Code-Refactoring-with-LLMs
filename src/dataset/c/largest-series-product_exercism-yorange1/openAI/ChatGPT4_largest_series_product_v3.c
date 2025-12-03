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

int64_t largest_series_product(char *digits, size_t span)
{
    assert(digits != NULL);

    size_t len = strlen(digits);
    if (span == 0)
    {
        return 1;
    }
    if (len == 0 || span > len)
    {
        return -1;
    }

    int64_t nums[len];
    if (!input_handle(digits, nums, len))
    {
        return -1;
    }

    int64_t max = 0, temp = 1;
    size_t zero_count = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (nums[i] == 0)
        {
            zero_count++;
        }
        else
        {
            temp *= nums[i];
        }

        if (i >= span)
        {
            if (nums[i - span] == 0)
            {
                zero_count--;
            }
            else
            {
                temp /= nums[i - span];
            }
        }

        if (zero_count == 0 && i >= span - 1)
        {
            if (temp > max)
            {
                max = temp;
            }
        }
    }

    return max;
}