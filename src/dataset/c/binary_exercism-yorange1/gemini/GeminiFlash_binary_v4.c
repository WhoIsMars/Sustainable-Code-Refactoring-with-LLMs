#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    int result = 0;
    const char *p = input;

    while (*p)
    {
        if (*p != '0' && *p != '1')
        {
            return INVALID;
        }

        result = (result << 1) | (*p - '0');
        p++;
    }

    return result;
}