#include "binary.h"
#include <stdbool.h>

int convert(const char *input) {
    if (input == NULL) {
        return INVALID;
    }

    int decimal = 0;
    const char *p = input;

    while (*p != '\0') {
        if (*p == '1') {
            if (decimal > (INT_MAX - 1) / 2) return INVALID;
            decimal = (decimal << 1) | 1;
        } else if (*p == '0') {
            if (decimal > INT_MAX / 2) return INVALID;
            decimal <<= 1;
        } else {
            return INVALID;
        }
        p++;
    }

    return decimal;
}