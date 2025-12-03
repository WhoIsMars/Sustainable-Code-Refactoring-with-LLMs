#include "binary.h"
#include <string.h>

int convert(const char *input)
{
    int result = 0;
    unsigned char index = strlen(input) - 1;

    while (*input != '\0')
    {
        if(*input == '1')
        {
            result += (1 << index);
        }
        else if(*input != '0')
        {
            result = INVALID;
            break;
        }
        index--;
        input++;
    }
    
    return result;
}

/*
Example:

"1111"
Length = 4

2^3 2^2 2^1 2^0
8   4   2   1
1   1   1   1  => 1 + 2 +  4 + 8 = 15  
*/
