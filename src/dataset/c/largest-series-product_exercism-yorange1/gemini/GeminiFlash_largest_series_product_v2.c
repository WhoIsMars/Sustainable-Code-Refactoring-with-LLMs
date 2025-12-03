#include "largest_series_product.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int64_t largest_series_product(char *digits, size_t span) {
    assert(digits != NULL);

    size_t len = strlen(digits);

    if (span == 0) {
        return 1;
    }

    if (len == 0 && span > 0) {
        return -1;
    }

    if (span > len) {
        return -1;
    }

    int64_t max_product = 0;

    for (size_t i = 0; i <= len - span; ++i) {
        int64_t current_product = 1;
        for (size_t j = 0; j < span; ++j) {
            if (!isdigit(digits[i + j])) {
                return -1;
            }
            int digit = digits[i + j] - '0';
            current_product *= digit;
            if (current_product == 0) {
                if (max_product < 0) continue;
                max_product = max_product > 0 ? max_product : 0;
                break;
            }
        }

        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}