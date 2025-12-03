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

    // Single pass comparison with early length mismatch detection
    while (lhs[i] != '\0' || rhs[i] != '\0')
    {
        // Check for length mismatch
        if (lhs[i] == '\0' || rhs[i] == '\0')
        {
            return -1;
        }
        
        if (lhs[i] != rhs[i])
        {
            ham_dist++;
        }
        
        i++;
    }

    return ham_dist;
}