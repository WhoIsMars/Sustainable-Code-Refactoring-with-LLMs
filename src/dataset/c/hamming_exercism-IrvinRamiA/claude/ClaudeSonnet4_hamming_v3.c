#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    if (!lhs || !rhs) {
        return -1;
    }
    
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
    
    if (*p1 || *p2) {
        return -1;
    }
    
    return counter;
}