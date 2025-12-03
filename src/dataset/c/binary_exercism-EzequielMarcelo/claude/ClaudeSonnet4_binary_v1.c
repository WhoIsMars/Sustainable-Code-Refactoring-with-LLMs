#include "binary.h"

int convert(const char *input) 
{
    if (input == NULL) 
        return INVALID;    

    int decimal = 0;
    const char *ptr = input;

    while (*ptr) 
    {
        if (*ptr == '1') {
            decimal = (decimal << 1) | 1;
        }
        else if (*ptr == '0') {
            decimal <<= 1;
        }
        else {
            return INVALID;
        }
        ptr++;
    }

    return decimal;
}