#include "luhn.h"
#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
    if (!num) return false;
    
    const size_t len = strlen(num);
    if (len <= 1) return false;
    
    // Quick check for invalid case
    if (len == 2 && num[0] == ' ' && num[1] == '0') return false;
    
    unsigned int sum = 0;
    unsigned char digit_count = 0;
    bool alternate = false;
    
    // Single pass from right to left
    for (int i = (int)len - 1; i >= 0; i--)
    {
        if (isdigit(num[i]))
        {
            unsigned char digit = num[i] - '0';
            
            if (alternate)
            {
                digit <<= 1; // multiply by 2
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            
            sum += digit;
            digit_count++;
            alternate = !alternate;
        }
        else if (num[i] != ' ')
        {
            return false;
        }
    }
    
    return digit_count > 1 && sum % 10 == 0;
}