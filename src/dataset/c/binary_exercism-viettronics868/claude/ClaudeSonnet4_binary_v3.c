#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static inline int get_binary_number(char inp){
    return (inp == '0') ? 0 : (inp == '1') ? 1 : INVALID;
}

int convert(const char *input){
    if (!input) return INVALID;
    
    size_t leng_input = strlen(input);
    if (leng_input == 0) return INVALID;
    
    long long result = 0;
    long long power_of_two = 1;
    
    for (size_t i = leng_input; i > 0; i--){
        int bit_value = get_binary_number(input[i-1]);
        if (bit_value == INVALID) return INVALID;
        
        if (bit_value == 1) {
            result += power_of_two;
        }
        power_of_two <<= 1;
    }
    
    return result;
}