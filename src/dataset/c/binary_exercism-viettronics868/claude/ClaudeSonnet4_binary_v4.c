#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int get_binary_number(char inp){
    return (inp == '0') ? 0 : (inp == '1') ? 1 : INVALID;
}

int convert(const char *input){
    if (!input) return INVALID;
    
    size_t leng_input = strlen(input);
    if (leng_input == 0) return INVALID;

    long long result = 0;
    long long power = 1;
    
    for (size_t i = leng_input; i > 0; i--){
        char current_char = input[i-1];
        if (current_char == '0'){
            power <<= 1;
        } else if (current_char == '1'){
            result += power;
            power <<= 1;
        } else {
            return INVALID;
        }
    }
    return result;
}