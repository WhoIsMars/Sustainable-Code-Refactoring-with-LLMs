#include "luhn.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool luhn(const char *num) {
    if (num == NULL) return false;

    size_t len = strlen(num);
    if (len <= 1) return false;

    size_t index = 0;
    unsigned int sum_digits = 0;
    bool double_digit = false;

    for (int i = len - 1; i >= 0; i--) {
        if (isdigit(num[i])) {
            int digit = num[i] - '0';

            if (double_digit) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }

            sum_digits += digit;
            double_digit = !double_digit;
            index++;
        } else if (num[i] != ' ') {
            return false;
        }
    }

    if (index == 0) return false; // No digits found

    return (sum_digits % 10 == 0);
}