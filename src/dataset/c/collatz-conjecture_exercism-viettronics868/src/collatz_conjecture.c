#include "collatz_conjecture.h"
#include <math.h>

int steps(int start){
    int pos_int = start;
    int count =0;
    if (pos_int <= 0) {
        count = -1;
        return count;
    }
    while (pos_int != 1){
        if ((pos_int % 2) == 0){
            pos_int = pos_int/2;
        } else { pos_int = (pos_int*3) + 1;}
        count++;
    }
    return count;
}