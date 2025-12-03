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
    for (size_t i = 0; i < length1; ++i)
    {
        counter += (lhs[i] != rhs[i]);
    }

    return counter;
}