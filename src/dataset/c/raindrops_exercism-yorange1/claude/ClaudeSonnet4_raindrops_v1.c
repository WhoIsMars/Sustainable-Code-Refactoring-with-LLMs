#include "raindrops.h"

#include <stdio.h>
#include <stdbool.h>

char *convert(char result[], int drops)
{
    char *ptr = result;
    bool has_factor = false;

    if (drops % 3 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'i'; *ptr++ = 'n'; *ptr++ = 'g';
        has_factor = true;
    }

    if (drops % 5 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'a'; *ptr++ = 'n'; *ptr++ = 'g';
        has_factor = true;
    }

    if (drops % 7 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'o'; *ptr++ = 'n'; *ptr++ = 'g';
        has_factor = true;
    }

    if (has_factor)
    {
        *ptr = '\0';
    }
    else
    {
        sprintf(result, "%d", drops);
    }

    return result;
}