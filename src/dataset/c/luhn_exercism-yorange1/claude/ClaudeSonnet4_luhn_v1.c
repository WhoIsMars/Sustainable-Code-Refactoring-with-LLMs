#include "luhn.h"

#include <ctype.h>
#include <stddef.h>

bool luhn(const char *num)
{
    if (!num || !num[0] || !num[1])
    {
        return false;
    }

    int sum = 0;
    bool need_double = false;
    size_t digit_count = 0;
    const char *p = num;

    // Find end of string
    while (*p) p++;
    p--;

    // Process from end to beginning
    while (p >= num)
    {
        char c = *p;
        if (c >= '0' && c <= '9')
        {
            int digit = c - '0';
            if (need_double)
            {
                digit <<= 1;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            sum += digit;
            need_double = !need_double;
            digit_count++;
        }
        else if (c != ' ')
        {
            return false;
        }
        p--;
    }

    return (sum % 10 == 0 && digit_count > 1);
}