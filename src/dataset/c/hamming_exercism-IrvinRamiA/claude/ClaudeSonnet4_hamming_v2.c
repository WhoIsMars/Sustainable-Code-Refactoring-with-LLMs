#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    size_t length = strlen(lhs);
    
    if (length != strlen(rhs))
    {
        return -1;
    }

    int counter = 0;
    const char *p1 = lhs;
    const char *p2 = rhs;
    const char *end = lhs + length;
    
    while (p1 < end)
    {
        if (*p1++ != *p2++)
        {
            counter++;
        }
    }

    return counter;
}