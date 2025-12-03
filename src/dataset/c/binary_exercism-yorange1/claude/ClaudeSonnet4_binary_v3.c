#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    if (!input) return INVALID;
    
    int result = 0;
    
    for (const char *p = input; *p; ++p)
    {
        if (*p != '0' && *p != '1')
        {
            return INVALID;
        }
        
        result = (result << 1) | (*p & 1);
    }
    
    return result;
}