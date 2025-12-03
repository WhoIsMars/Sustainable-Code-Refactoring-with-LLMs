#include "hamming.h"

int compute(const char *lhs, const char *rhs) 
{
    size_t length1 = 0;
    size_t length2 = 0;
    int distance = 0;

    if (lhs == NULL || rhs == NULL) 
        return -1;    

    while (lhs[length1] != '\0') 
        length1++;
    
    while (rhs[length2] != '\0') 
        length2++;
    
    if (length1 != length2) 
        return -1;      
   
    for (size_t i = 0; i < length1; i++) 
    {
        if (lhs[i] != rhs[i]) 
            distance++; 
    }

    return distance;
}