#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int convert(const char *input){
    if (!input) return INVALID;
    
    size_t leng_input = strlen(input);
    if (leng_input == 0) return INVALID;

    long long result = 0;
    for (size_t i = 0; i < leng_input; i++){
        char bit = input[i];
        if (bit == '1'){
            result = (result << 1) | 1;
        } else if (bit == '0'){
            result = result << 1;
        } else {
            return INVALID;
        }
    }
    return result;
}