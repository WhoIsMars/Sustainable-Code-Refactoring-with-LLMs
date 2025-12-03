#include "luhn.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

bool luhn(const char *num)
{
    if (!num || !*num)
    {
        return false;
    }

    int sum = 0;
    bool need_double = false;
    size_t digit_count = 0;

    for (const char *ptr = num + strlen(num) - 1; ptr >= num; --ptr)
    {
        char c = *ptr;
        if (isdigit(c))
        {
            int digit = c - '0';
            if (need_double)
            {
                digit = (digit > 4) ? (digit * 2 - 9) : (digit * 2);
            }
            sum += digit;
            need_double = !need_double;
            digit_count++;
        }
        else if (c != ' ')
        {
            return false;
        }
    }

    return (sum % 10 == 0 && digit_count > 1);
}