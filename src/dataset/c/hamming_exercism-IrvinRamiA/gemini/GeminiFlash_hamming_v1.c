#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs) {
    size_t len = strlen(lhs);
    if (len != strlen(rhs)) {
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < len; ++i) {
        distance += (lhs[i] != rhs[i]);
    }

    return distance;
}