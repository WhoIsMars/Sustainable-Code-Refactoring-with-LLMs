#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    size_t length1 = strlen(lhs);
    size_t length2 = strlen(rhs);

    if (length1 != length2)
    {
        return -1;
    }

    int counter = 0;
    const char *p1 = lhs;
    const char *p2 = rhs;
    const char *end = lhs + length1;

    while (p1 < end)
    {
        if (*p1++ != *p2++)
        {
            counter++;
        }
    }

    return counter;
}