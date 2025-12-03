#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    int h = 0;
    
    while (*lhs && *rhs)
    {
        if (*lhs != *rhs)
            h++;
        lhs++;
        rhs++;
    }
    
    if (*lhs || *rhs)
        return -1;
    
    return h;
}