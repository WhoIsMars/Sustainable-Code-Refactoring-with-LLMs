#include "hamming.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int compute(const char *lhs, const char *rhs){
    if (lhs == NULL || rhs == NULL){
        return -1;
    }
    
    size_t length_lhs = strlen(lhs);
    size_t length_rhs = strlen(rhs);

    if (length_lhs != length_rhs){
        return -1;
    }
    
    if (length_lhs == 0) {
        return 0;
    }
    
    int hamming_distance = 0;
    for (size_t i = 0; i < length_lhs; i++){
        hamming_distance += (lhs[i] != rhs[i]);
    }
    
    return hamming_distance;
}