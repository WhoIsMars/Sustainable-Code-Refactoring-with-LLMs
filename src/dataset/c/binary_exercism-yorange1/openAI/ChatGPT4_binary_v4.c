#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    int result = 0;

    for (; *input; input++)
    {
        if (*input != '0' && *input != '1')
        {
            return INVALID;
        }

        result = (result << 1) | (*input - '0');
    }

    return result;
}