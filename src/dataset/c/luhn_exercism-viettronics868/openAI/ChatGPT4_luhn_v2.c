#include "luhn.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool luhn(const char *num) {
    if (!num || *num == '\0') return false;

    int sum = 0;
    bool alternate = false;
    size_t length = 0;

    // Process the string in reverse, skipping spaces and validating digits
    for (const char *ptr = num + strlen(num) - 1; ptr >= num; --ptr) {
        if (isspace(*ptr)) continue;
        if (!isdigit(*ptr)) return false;

        int digit = *ptr - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
        length++;
    }

    // A valid Luhn number must have at least two digits and sum divisible by 10
    return length > 1 && sum % 10 == 0;
}