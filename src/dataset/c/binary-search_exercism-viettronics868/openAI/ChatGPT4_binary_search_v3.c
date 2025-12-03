#include "binary_search.h"
#include <stddef.h>

const int *binary_search(int value, const int *arr, size_t length) {
    size_t low = 0, high = length;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == value) {
            return &arr[mid];
        } else if (value < arr[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return NULL;
}