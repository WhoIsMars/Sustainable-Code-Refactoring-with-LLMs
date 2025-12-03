#include "binary_search.h"
#include <stddef.h>

const int *binary_search(int value, const int *arr, size_t length) {
    while (length > 0) {
        size_t half_length = length / 2;
        const int *mid = arr + half_length;

        if (value == *mid) {
            return mid;
        } else if (value < *mid) {
            length = half_length;
        } else {
            arr = mid + 1;
            length -= half_length + 1;
        }
    }
    return NULL;
}