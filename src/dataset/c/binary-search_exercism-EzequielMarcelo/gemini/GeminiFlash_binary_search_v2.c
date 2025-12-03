#include "binary_search.h"

const int* binary_search(int value, const int* arr, size_t length) {
    if (arr == NULL || length == 0) {
        return NULL;
    }

    size_t low = 0;
    size_t high = length; // Corrected high initialization

    while (low < high) { // Changed loop condition
        size_t mid = low + (high - low) / 2; // Prevent potential overflow

        if (arr[mid] == value) {
            return &arr[mid];
        } else if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid; // Corrected high update
        }
    }

    return NULL;
}