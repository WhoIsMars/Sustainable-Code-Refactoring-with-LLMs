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

    // Single pass comparison with length validation
    while (lhs[i] != '\0' || rhs[i] != '\0')
    {
        if (lhs[i] == '\0' || rhs[i] == '\0')
        {
            return -1; // Different lengths
        }
        
        if (lhs[i] != rhs[i])
        {
            ham_dist++;
        }
        
        i++;
    }

    return ham_dist;
}