#include "raindrops.h"

#include <stdio.h>
#include <string.h>

char *convert(char result[], int drops)
{
    int len = 0;

    if (drops % 3 == 0)
    {
        memcpy(result + len, "Pling", 5);
        len += 5;
    }

    if (drops % 5 == 0)
    {
        memcpy(result + len, "Plang", 5);
        len += 5;
    }

    if (drops % 7 == 0)
    {
        memcpy(result + len, "Plong", 5);
        len += 5;
    }

    if (len == 0)
    {
        sprintf(result, "%d", drops);
    }
    else
    {
        result[len] = '\0';
    }

    return result;
}