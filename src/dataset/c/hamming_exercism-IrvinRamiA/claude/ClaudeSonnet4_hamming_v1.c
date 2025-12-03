#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    // Single pass comparison with early length mismatch detection
    int counter = 0;
    const char *p1 = lhs;
    const char *p2 = rhs;
    
    while (*p1 && *p2) {
        if (*p1 != *p2) {
            counter++;
        }
        p1++;
        p2++;
    }
    
    // Check if strings have different lengths
    if (*p1 || *p2) {
        return -1;
    }
    
    return counter;
}