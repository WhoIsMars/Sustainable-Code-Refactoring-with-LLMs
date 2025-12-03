#include "hamming.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int compute(const char *lhs, const char *rhs){
    if (lhs == NULL || rhs == NULL){
        return -1;
    }
    
    // Single pass to check length equality and compute distance
    int hamming_distance = 0;
    size_t i = 0;
    
    // Process characters while both strings have characters
    while (lhs[i] != '\0' && rhs[i] != '\0') {
        if (lhs[i] != rhs[i]) {
            hamming_distance++;
        }
        i++;
    }
    
    // Check if strings have different lengths
    if (lhs[i] != rhs[i]) {
        return -1;
    }
    
    return hamming_distance;
}