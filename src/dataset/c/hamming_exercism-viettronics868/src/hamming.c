#include "hamming.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int compute(const char *lhs, const char *rhs){
    if (lhs == NULL || rhs == NULL){
        return -1;
    }
    
    int haming_distance = 0;
    size_t length_lhs = strlen(lhs);
    size_t length_rhs = strlen(rhs);

    if ((length_lhs != length_rhs)){
        return -1;
    } else if ((length_rhs == 0)) return 0;
    else    
    {
        for (size_t i = 0; i <= (length_lhs -1); i++){
  
            if (lhs[i] != rhs[i]) haming_distance += 1;
        }
    }
    return haming_distance;
    
}