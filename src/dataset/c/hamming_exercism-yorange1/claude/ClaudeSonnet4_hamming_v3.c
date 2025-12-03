#include "hamming.h"

#include <stddef.h>

int compute(const char *lhs, const char *rhs)
{
    if (NULL == lhs || NULL == rhs)
    {
        return -1;
    }

    int ham_dist = 0;
    size_t i = 0;

    while (lhs[i] && rhs[i])
    {
        if (lhs[i] != rhs[i])
        {
            ham_dist++;
        }
        i++;
    }

    if (lhs[i] || rhs[i])
    {
        return -1;
    }

    return ham_dist;
}