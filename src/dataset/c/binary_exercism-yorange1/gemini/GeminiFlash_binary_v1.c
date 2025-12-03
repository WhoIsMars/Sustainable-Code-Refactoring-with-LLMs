#include "binary.h"

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

int convert(const char *input)
{
    int result = 0;
    const char *p = input;

    if (input == NULL) {
        return INVALID;
    }

    while (*p != '\0')
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