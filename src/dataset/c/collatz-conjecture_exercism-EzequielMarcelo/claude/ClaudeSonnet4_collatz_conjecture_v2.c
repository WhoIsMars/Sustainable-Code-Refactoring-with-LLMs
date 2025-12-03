#include "collatz_conjecture.h"

int steps(int start)
{
    if (start <= 0) 
       return ERROR_VALUE;
    
    int step_count = 0;
    
    while (start != 1) 
    {
        if (start & 1) {
            start = 3 * start + 1;
        } else {
            start >>= 1;
        }
        step_count++;
    }
    
    return step_count;
}