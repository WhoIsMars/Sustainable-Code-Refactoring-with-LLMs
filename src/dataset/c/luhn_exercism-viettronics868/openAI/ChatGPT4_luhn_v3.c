#include "luhn.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool luhn(const char *num) {
    if (!num || *num == '\0') return false;

    int sum = 0, len = 0, double_digit = 0;
    bool is_second = false;

    for (const char *p = num; *p; ++p) {
        if (isspace(*p)) continue;
        if (!isdigit(*p)) return false;

        int digit = *p - '0';
        if (is_second) {
            double_digit = digit * 2;
            sum += (double_digit > 9) ? double_digit - 9 : double_digit;
        } else {
            sum += digit;
        }
        is_second = !is_second;
        len++;
    }

    if (len <= 1) return false;
    return (sum % 10) == 0;
}