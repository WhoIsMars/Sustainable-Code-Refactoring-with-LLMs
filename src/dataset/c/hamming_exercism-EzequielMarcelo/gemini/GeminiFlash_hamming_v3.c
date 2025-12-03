#include "hamming.h"
#include <string.h>

int compute(const char *lhs, const char *rhs) {
    if (lhs == NULL || rhs == NULL) {
        return -1;
    }

    size_t length = strlen(lhs);
    if (length != strlen(rhs)) {
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < length; ++i) {
        distance += (lhs[i] != rhs[i]);
    }

    return distance;
}