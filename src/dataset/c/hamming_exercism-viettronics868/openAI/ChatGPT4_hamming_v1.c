#include "hamming.h"
#include <stddef.h>

int compute(const char *lhs, const char *rhs) {
    if (!lhs || !rhs) {
        return -1;
    }

    int hamming_distance = 0;
    for (size_t i = 0; lhs[i] && rhs[i]; i++) {
        if (lhs[i] != rhs[i]) {
            hamming_distance++;
        }
    }

    return (lhs[hamming_distance] || rhs[hamming_distance]) ? -1 : hamming_distance;
}