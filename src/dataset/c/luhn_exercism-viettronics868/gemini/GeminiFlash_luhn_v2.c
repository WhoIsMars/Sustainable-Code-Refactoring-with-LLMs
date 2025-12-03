#include "luhn.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool luhn(const char *num) {
    if (num == NULL || *num == '\0') {
        return false;
    }

    size_t len = strlen(num);
    if (len <= 1) {
        return false;
    }

    int sum = 0;
    int digits = 0;

    // Iterate backwards, skipping whitespace
    for (size_t i = len; i > 0; i--) {
        char c = num[i - 1];
        if (isspace(c)) {
            continue;
        }

        if (!isdigit(c)) {
            return false;
        }

        int digit = c - '0';
        
        if (digits % 2 == 1) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        digits++;
    }

    if (digits <= 1) return false;

    return (sum % 10) == 0;
}