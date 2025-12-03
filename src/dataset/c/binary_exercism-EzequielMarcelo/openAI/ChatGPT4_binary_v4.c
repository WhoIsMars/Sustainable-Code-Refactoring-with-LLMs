#include "binary.h"

int convert(const char *input) 
{
    if (!input) 
        return INVALID;

    int decimal = 0;
    for (char c; (c = *input) != '\0'; input++) 
    {
        if (c == '1')
            decimal = (decimal << 1) | 1;
        else if (c == '0') 
            decimal <<= 1;
        else 
            return INVALID;
    }

    return decimal;
}