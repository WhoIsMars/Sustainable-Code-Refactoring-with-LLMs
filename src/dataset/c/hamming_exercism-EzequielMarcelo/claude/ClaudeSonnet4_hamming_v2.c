#include "hamming.h"

int compute(const char *lhs, const char *rhs) 
{
    if (lhs == NULL || rhs == NULL) 
        return -1;    

    int distance = 0;
    size_t i = 0;
    
    while (lhs[i] != '\0' && rhs[i] != '\0') {
        if (lhs[i] != rhs[i]) 
            distance++;
        i++;
    }
    
    if (lhs[i] != rhs[i])
        return -1;
    
    return distance;
}