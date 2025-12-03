#include "binary.h"

int convert(const char *input) 
{
    size_t len = strlen(input);
    int decimal = 0;

    if (input == NULL) 
        return INVALID;    

    for (size_t i = 0; i < len; i++) 
    {
        if (input[i] == '1')
            decimal = decimal * 2 + 1;

        else if (input[i] == '0') 
            decimal = decimal * 2;

        else 
            return INVALID; 
    }

    return decimal;
}