#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    int h = 0;
    const char *lhs_ptr = lhs;
    const char *rhs_ptr = rhs;
    
    // Single pass to check length equality and compute hamming distance
    while (*lhs_ptr && *rhs_ptr) {
        if (*lhs_ptr != *rhs_ptr)
            h++;
        lhs_ptr++;
        rhs_ptr++;
    }
    
    // If one string ended before the other, lengths are different
    if (*lhs_ptr || *rhs_ptr)
        return -1;
    
    return h;
}