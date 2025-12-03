#include "binary.h"

int convert(const char *input)
{
    int result = 0;
    
    for (const char *p = input; *p != '\0'; p++)
    {
        if (*p == '1')
        {
            result = (result << 1) | 1;
        }
        else if (*p == '0')
        {
            result <<= 1;
        }
        else
        {
            return INVALID;
        }
    }
    
    return result;
}