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

    unsigned char counter = 0;
    for (size_t i = 0; i < length; i++)
    {
        counter += (lhs[i] != rhs[i]);
    }

    return counter;
}