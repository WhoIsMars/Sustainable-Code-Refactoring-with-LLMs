#include "binary.h"
#include <string.h>
#include <ctype.h>

int convert(const char *input) {
    if (input == NULL) {
        return INVALID;
    }

    int decimal = 0;
    const char *p = input;

    while (*p != '\0') {
        if (*p == '1') {
            if (decimal > (INT_MAX - 1) / 2) return INVALID; // Check for potential overflow
            decimal = (decimal << 1) | 1; // Equivalent to decimal * 2 + 1, but faster
        } else if (*p == '0') {
            if (decimal > INT_MAX / 2) return INVALID; // Check for potential overflow
            decimal <<= 1; // Equivalent to decimal * 2, but faster
        } else {
            return INVALID;
        }
        p++;
    }

    return decimal;
}