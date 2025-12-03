#include "binary.h"

int convert(const char *input) 
{
    if (input == NULL) 
        return INVALID;

    int decimal = 0;
    
    for (const char *p = input; *p; p++) 
    {
        if (*p == '1') {
            decimal = (decimal << 1) | 1;
        }
        else if (*p == '0') {
            decimal <<= 1;
        }
        else {
            return INVALID;
        }
    }

    return decimal;
}