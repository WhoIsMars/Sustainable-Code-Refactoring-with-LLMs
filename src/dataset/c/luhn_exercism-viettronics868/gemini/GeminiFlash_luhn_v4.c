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
    bool alt = false;
    for (size_t i = len; i-- > 0;) {
        if (isspace(num[i])) {
            continue;
        }
        if (!isdigit(num[i])) {
            return false;
        }

        int digit = num[i] - '0';

        if (alt) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        alt = !alt;
    }

    return (sum % 10 == 0);
}