#include "luhn.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool luhn(const char *num) {
    if (!num || *num == '\0') {
        return false;
    }

    size_t len = strlen(num);
    if (len <= 1) {
        return false;
    }

    int sum = 0;
    int digits = 0;

    for (long i = (long)len - 1; i >= 0; --i) {
        if (isspace(num[i])) {
            continue;
        }

        if (!isdigit(num[i])) {
            return false;
        }

        int digit = num[i] - '0';
        
        if (digits % 2 != 0) {
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