#include "hamming.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int compute(const char *lhs, const char *rhs){
    if (lhs == NULL || rhs == NULL){
        return -1;
    }
    
    // Check lengths while computing distance in single pass
    int hamming_distance = 0;
    size_t i = 0;
    
    // Single pass comparison with early termination
    while (lhs[i] != '\0' || rhs[i] != '\0') {
        // If one string ends before the other, lengths differ
        if (lhs[i] == '\0' || rhs[i] == '\0') {
            return -1;
        }
        
        if (lhs[i] != rhs[i]) {
            hamming_distance++;
        }
        i++;
    }
    
    return hamming_distance;
}