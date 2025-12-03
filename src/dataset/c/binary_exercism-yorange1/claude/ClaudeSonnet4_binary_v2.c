#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    int result = 0;
    const char *ptr = input;

    while (*ptr)
    {
        if (*ptr != '0' && *ptr != '1')
        {
            return INVALID;
        }

        result = (result << 1) | (*ptr & 1);
        ptr++;
    }

    return result;
}