#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
    int sum = 0;
    bool need_double = false;
    int digit_count = 0;

    for (const char *p = num; *p; ++p)
    {
        if (!isdigit(*p) && *p != ' ')
        {
            return false;
        }
    }

    for (const char *p = num + strlen(num) - 1; p >= num; --p)
    {
        if (isdigit(*p))
        {
            int digit = *p - '0';
            if (need_double)
            {
                digit = (digit > 4) ? (digit * 2 - 9) : (digit * 2);
            }
            sum += digit;
            need_double = !need_double;
            digit_count++;
        }
    }

    return (sum % 10 == 0 && digit_count > 1);
}