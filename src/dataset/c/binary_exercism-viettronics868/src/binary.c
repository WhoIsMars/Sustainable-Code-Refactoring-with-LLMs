#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

int get_binary_number(char inp){
    switch (inp){
        case '0': return 0;
        case '1': return 1;
        default: return INVALID;
    }
}

int convert(const char *input){
    size_t leng_input = strlen(input);

    long long result = 0;
    if (leng_input == 0) return INVALID;
    for (size_t i = 0; i < leng_input; i++){
        if (get_binary_number(input[leng_input-1-i]) != INVALID){
            result += (get_binary_number(input[leng_input-1-i])*pow(2, (i)));//start from the least bit
       
        } else return INVALID;
    }
    return result;
}