#include "luhn.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool luhn(const char *num) {
    if (!num || *num == '\0') return false;

    int sum = 0, len = 0, is_second = 0;

    for (const char *p = num; *p; ++p) {
        if (isspace(*p)) continue;
        if (!isdigit(*p)) return false;

        int digit = *p - '0';
        if (is_second) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        is_second = !is_second;
        ++len;
    }

    return len > 1 && sum % 10 == 0;
}