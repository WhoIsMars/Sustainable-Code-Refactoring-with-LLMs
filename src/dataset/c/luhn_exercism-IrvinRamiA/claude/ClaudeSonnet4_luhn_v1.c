#include "luhn.h"
#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
    int len = strlen(num);
    
    if (len <= 1 || (num[0] == ' ' && num[1] == '0' && len == 2))
    {
        return false;
    }

    unsigned int sum_digits = 0;
    unsigned char digit_count = 0;

    // Single pass from right to left
    for (int i = len - 1; i >= 0; i--)
    {
        if (isdigit(num[i]))
        {
            int digit = num[i] - '0';
            
            if (digit_count % 2 == 1) // Every second digit from right
            {
                digit *= 2;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            
            sum_digits += digit;
            digit_count++;
        }
        else if (num[i] != ' ')
        {
            return false;
        }
    }

    return sum_digits % 10 == 0;
}