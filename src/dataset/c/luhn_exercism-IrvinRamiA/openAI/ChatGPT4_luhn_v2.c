#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief This function checks if the given number complies with luhn algorithm
 *
 * @param num
 * @return true
 * @return false
 */
bool luhn(const char *num)
{
    unsigned int len = strlen(num);
    unsigned int sum_digits = 0;
    bool is_second = false;

    if (len <= 1)
    {
        return false;
    }

    for (int i = len - 1; i >= 0; i--)
    {
        if (isdigit(num[i]))
        {
            int digit = num[i] - '0';

            if (is_second)
            {
                digit *= 2;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }

            sum_digits += digit;
            is_second = !is_second;
        }
        else if (num[i] != ' ')
        {
            return false;
        }
    }

    return (sum_digits % 10 == 0);
}