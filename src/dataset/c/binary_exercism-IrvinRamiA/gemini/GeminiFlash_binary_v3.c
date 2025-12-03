#include "binary.h"
#include <string.h>
#include <stddef.h>

int convert(const char *input)
{
    int result = 0;
    size_t len = strlen(input);

    if (len > 31) return INVALID;

    for (size_t i = 0; i < len; ++i)
    {
        if (input[i] == '1')
        {
            result = (result << 1) | 1;
        }
        else if (input[i] == '0')
        {
            result = result << 1;
        }
        else
        {
            return INVALID;
        }
    }

    return result;
}