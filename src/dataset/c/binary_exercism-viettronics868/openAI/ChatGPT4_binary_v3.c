#include "binary.h"
#include <string.h>
#include <stdint.h>

int get_binary_number(char inp) {
    return (inp == '0' || inp == '1') ? inp - '0' : INVALID;
}

int convert(const char *input) {
    size_t leng_input = strlen(input);
    if (leng_input == 0) return INVALID;

    long long result = 0;
    for (size_t i = 0; i < leng_input; i++) {
        int bit = get_binary_number(input[i]);
        if (bit == INVALID) return INVALID;
        result = (result << 1) | bit;
    }
    return result;
}