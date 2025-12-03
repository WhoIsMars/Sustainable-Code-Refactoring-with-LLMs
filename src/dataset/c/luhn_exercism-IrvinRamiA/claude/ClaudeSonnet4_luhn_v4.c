#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool luhn(const char *num)
{
    if (!num) return false;
    
    size_t len = strlen(num);
    if (len <= 1) return false;
    
    unsigned int sum = 0;
    unsigned char digit_count = 0;
    bool alternate = false;
    
    for (int i = len - 1; i >= 0; i--)
    {
        char c = num[i];
        
        if (isdigit(c))
        {
            unsigned char digit = c - '0';
            digit_count++;
            
            if (alternate)
            {
                digit <<= 1;
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