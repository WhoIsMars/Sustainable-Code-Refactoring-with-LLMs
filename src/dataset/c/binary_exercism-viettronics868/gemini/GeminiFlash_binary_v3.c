#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int get_binary_number(char inp){
    if (inp == '0') return 0;
    if (inp == '1') return 1;
    return INVALID;
}

int convert(const char *input){
    size_t leng_input = strlen(input);

    if (leng_input == 0) return INVALID;

    long long result = 0;
    long long power_of_2 = 1;

    for (size_t i = 0; i < leng_input; i++){
        int digit = get_binary_number(input[leng_input-1-i]);
        if (digit != INVALID){
            result += (digit * power_of_2);
            if (i < leng_input - 1) {
                if (power_of_2 > (LLONG_MAX / 2)) return INVALID;
                power_of_2 *= 2;
            }
        } else return INVALID;
    }
    return result;
}