#include "hamming.h"

#include <stddef.h>
#include <string.h>

int compute(const char *lhs, const char *rhs)
{
    if (lhs == NULL || rhs == NULL)
    {
        return -1;
    }

    size_t lhs_len = strlen(lhs);
    size_t rhs_len = strlen(rhs);

    if (lhs_len != rhs_len)
    {
        return -1;
    }

    int ham_dist = 0;
    size_t i = 0;

    while (i < lhs_len)
    {
        ham_dist += (lhs[i] != rhs[i]);
        i++;
    }

    return ham_dist;
}