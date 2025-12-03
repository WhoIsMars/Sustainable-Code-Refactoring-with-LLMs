#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    unsigned char len = strlen(num);
    char *num_copy = (char *)malloc(len * sizeof(char));
    unsigned char index = 0;
    unsigned int sum_digits = 0;
    bool result = false;

    if (len <= 1 || (num[0] == ' ' && num[1] == '0' && len == 2))
    {
        return false;
    }

    strncpy(num_copy, num, len);

    for (int i = len - 1; i >= 0; i--)
    {
        if (isdigit(num_copy[i]))
        {
            if ((index + 1) % 2 == 0)
            {
                num_copy[i] = (((num_copy[i] - '0') * 2) + '0');

                if (num_copy[i] > '9')
                {
                    num_copy[i] = (num_copy[i] - '9') + '0';
                }
            }
            index++;
        }
        else if (num_copy[i] != ' ')
        {
            return false;
        }
    }

    for (unsigned i = 0; i < len; i++)
    {
        if (isdigit(num_copy[i]))
        {
            sum_digits += (num_copy[i] - '0');
        }
    }

    if (sum_digits % 10 == 0)
    {
        result = true;
    }

    return result;
}
