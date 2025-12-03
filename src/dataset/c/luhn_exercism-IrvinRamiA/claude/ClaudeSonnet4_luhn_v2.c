#include "luhn.h"
#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
    int len = strlen(num);
    int sum = 0;
    int digit_count = 0;
    bool alternate = false;

    if (len <= 1)
    {
        return false;
    }

    // Single pass from right to left
    for (int i = len - 1; i >= 0; i--)
    {
        char c = num[i];
        
        if (isdigit(c))
        {
            int digit = c - '0';
            digit_count++;
            
            if (alternate)
            {
                digit *= 2;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            
            sum += digit;
            alternate = !alternate;
        }
        else if (c != ' ')
        {
            return false;
        }
    }

    return digit_count > 1 && sum % 10 == 0;
}