#include "hamming.h"

#include <stddef.h>

int compute(const char *lhs, const char *rhs)
{
    if (!lhs || !rhs)
    {
        return -1;
    }

    int ham_dist = 0;

    for (size_t i = 0; lhs[i] && rhs[i]; i++)
    {
        if (lhs[i] != rhs[i])
        {
            ham_dist++;
        }
    }

    return (lhs[0] && rhs[0]) ? ham_dist : -1;
}