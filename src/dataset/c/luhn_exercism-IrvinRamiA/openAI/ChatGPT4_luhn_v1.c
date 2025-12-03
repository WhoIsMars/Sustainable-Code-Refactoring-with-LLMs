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
 *
 * Useful information:
 * '0' -> DEC 48 -> HEX 0x30
 */
bool luhn(const char *num)
{
    unsigned int len = strlen(num);
    unsigned int sum_digits = 0;
    bool double_digit = false;

    if (len <= 1 || (num[0] == ' ' && num[1] == '0' && len == 2))
    {
        return false;
    }

    for (int i = len - 1; i >= 0; i--)
    {
        if (isdigit(num[i]))
        {
            unsigned int digit = num[i] - '0';
            if (double_digit)
            {
                digit *= 2;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            sum_digits += digit;
            double_digit = !double_digit;
        }
        else if (num[i] != ' ')
        {
            return false;
        }
    }

    return (sum_digits % 10 == 0);
}