#include "luhn.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool luhn(const char *num) {
    if (!num || *num == '\0') return false;

    int sum = 0, digit, double_digit;
    bool alternate = false;
    size_t len = strlen(num);

    if (len <= 1) return false;

    for (int i = len - 1; i >= 0; i--) {
        if (isspace(num[i])) continue;
        if (!isdigit(num[i])) return false;

        digit = num[i] - '0';
        if (alternate) {
            double_digit = digit * 2;
            sum += (double_digit > 9) ? double_digit - 9 : double_digit;
        } else {
            sum += digit;
        }
        alternate = !alternate;
    }

    return (sum % 10) == 0;
}