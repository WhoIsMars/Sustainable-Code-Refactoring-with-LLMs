#include "binary.h"

int convert(const char *input) 
{
    if (input == NULL) 
        return INVALID;

    int decimal = 0;

    for (const char *ptr = input; *ptr != '\0'; ++ptr) 
    {
        if (*ptr == '1')
            decimal = (decimal << 1) | 1;
        else if (*ptr == '0') 
            decimal = decimal << 1;
        else 
            return INVALID; 
    }

    return decimal;
}