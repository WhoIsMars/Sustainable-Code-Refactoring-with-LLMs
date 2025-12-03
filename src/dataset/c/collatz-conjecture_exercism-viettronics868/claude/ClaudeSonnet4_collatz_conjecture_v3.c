#include "collatz_conjecture.h"

int steps(int start){
    if (start <= 0) {
        return -1;
    }
    
    int count = 0;
    int n = start;
    
    while (n != 1) {
        if (n & 1) {
            n = n * 3 + 1;
        } else {
            n >>= 1;
        }
        count++;
    }
    
    return count;
}