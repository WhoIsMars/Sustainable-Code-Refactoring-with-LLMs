#include "hamming.h"

#include <stddef.h>

int compute(const char *lhs, const char *rhs)
{
    if (!lhs || !rhs)
    {
        return -1;
    }

    int ham_dist = 0;

    for (; *lhs && *rhs; ++lhs, ++rhs)
    {
        if (*lhs != *rhs)
        {
            ++ham_dist;
        }
    }

    return (*lhs || *rhs) ? -1 : ham_dist;
}