#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int convert(const char *input){
    if (!input || *input == '\0') return INVALID;
    
    long long result = 0;
    const char *ptr = input;
    
    // First pass: validate all characters
    while (*ptr) {
        if (*ptr != '0' && *ptr != '1') return INVALID;
        ptr++;
    }
    
    // Second pass: convert using bit shifting
    ptr = input;
    while (*ptr) {
        result = (result << 1) + (*ptr - '0');
        ptr++;
    }
    
    return result;
}