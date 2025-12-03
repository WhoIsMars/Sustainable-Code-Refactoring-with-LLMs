#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool luhn(const char *num) {
    size_t len = strlen(num);
    if (len <= 1) {
        return false;
    }

    unsigned int sum = 0;
    bool alt = false;

    for (int i = (int)len - 1; i >= 0; i--) {
        if (isspace(num[i])) {
            continue;
        } else if (!isdigit(num[i])) {
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