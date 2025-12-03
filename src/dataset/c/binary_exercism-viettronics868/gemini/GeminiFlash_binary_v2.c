#include "binary.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int get_binary_number(char inp) {
    if (inp == '0') return 0;
    if (inp == '1') return 1;
    return INVALID;
}

int convert(const char *input) {
    size_t len = strlen(input);
    if (len == 0) return INVALID;

    long long result = 0;
    long long power_of_2 = 1;

    for (size_t i = len; i > 0; --i) {
        int digit = get_binary_number(input[i - 1]);
        if (digit == INVALID) return INVALID;
        result += digit * power_of_2;
        if (i > 1 && result > INT_MAX) return INVALID; // Check for overflow before next multiplication
        power_of_2 *= 2;
    }

    if (result > INT_MAX) return INVALID;

    return (int)result;
}