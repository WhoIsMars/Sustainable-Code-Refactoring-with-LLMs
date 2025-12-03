#include "binary.h"

int convert(const char *input) 
{
    if (input == NULL) 
        return INVALID;

    int decimal = 0;
    char c;

    while ((c = *input++) != '\0') 
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