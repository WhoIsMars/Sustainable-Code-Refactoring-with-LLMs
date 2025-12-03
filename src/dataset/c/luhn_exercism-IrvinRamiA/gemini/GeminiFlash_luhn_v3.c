#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool luhn(const char *num) {
    size_t len = strlen(num);
    if (len <= 1) {
        return false;
    }

    size_t sum = 0;
    bool alt = false;
    for (int i = len - 1; i >= 0; i--) {
        if (isspace(num[i])) {
            continue;
        }
        if (!isdigit(num[i])) {
            return false;
        }

        int n = num[i] - '0';

        if (alt) {
            n *= 2;
            if (n > 9) {
                n -= 9;
            }
        }
        sum += n;
        alt = !alt;
    }

    return (sum % 10 == 0);
}