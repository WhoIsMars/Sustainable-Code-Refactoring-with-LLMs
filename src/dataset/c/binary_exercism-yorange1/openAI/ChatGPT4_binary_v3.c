#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    int result = 0;

    for (const char *ptr = input; *ptr; ++ptr)
    {
        if (*ptr != '0' && *ptr != '1')
        {
            return INVALID;
        }

        result = (result << 1) | (*ptr - '0');
    }

    return result;
}