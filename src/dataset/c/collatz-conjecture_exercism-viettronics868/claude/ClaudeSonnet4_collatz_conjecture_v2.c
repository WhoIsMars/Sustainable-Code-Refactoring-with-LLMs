#include "collatz_conjecture.h"

int steps(int start){
    if (start <= 0) {
        return -1;
    }
    
    int count = 0;
    int pos_int = start;
    
    while (pos_int != 1){
        if (pos_int & 1) {
            pos_int = pos_int * 3 + 1;
        } else {
            pos_int >>= 1;
        }
        count++;
    }
    return count;
}