#include "binary.h"
#include <string.h>
#include <stddef.h>

int convert(const char *input)
{
    int result = 0;
    size_t len = strlen(input);

    for (size_t i = 0; i < len; ++i)
    {
        if (input[i] == '1')
        {
            if (result > (INT_MAX >> 1)) return INVALID; // Check for potential overflow before shifting
            result = (result << 1) | 1;
        }
        else if (input[i] == '0')
        {
            if (result > (INT_MAX >> 1)) return INVALID; // Check for potential overflow before shifting
            result = result << 1;
        }
        else
        {
            return INVALID;
        }
    }

    return result;
}