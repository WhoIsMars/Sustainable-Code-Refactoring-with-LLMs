#include "binary_search.h"
#include <stddef.h>

const int *binary_search(int value, const int *arr, size_t length) {
    size_t low = 0;
    size_t high = length;

    while (low < high) {
        size_t mid = low + (high - low) / 2;  // Prevent potential overflow
        if (arr[mid] == value) {
            return &arr[mid];
        } else if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return NULL;
}