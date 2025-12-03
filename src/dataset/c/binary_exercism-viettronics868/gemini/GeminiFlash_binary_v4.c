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
    size_t len = strlen(input);
    if (len == 0) return INVALID;

    long long result = 0;
    for (size_t i = 0; i < len; i++) {
        char c = input[len - 1 - i];
        int digit = get_binary_number(c);
        if (digit == INVALID) {
            return INVALID;
        }
        if (digit == 1) {
            if (i >= 63) return INVALID; // Prevent overflow
            result |= (1LL << i);
        }
    }
    return result;
}