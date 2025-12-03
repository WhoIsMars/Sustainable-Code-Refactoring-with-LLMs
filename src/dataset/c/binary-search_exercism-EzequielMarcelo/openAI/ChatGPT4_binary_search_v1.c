#include "binary_search.h"

const int* binary_search(int value, const int* arr, size_t length) {
    if (!arr || length == 0)
        return NULL;

    size_t low = 0, high = length - 1;

    while (low <= high) {
        size_t mid = (low + high) >> 1; // Use bitwise shift for division by 2
        if (arr[mid] == value)
            return &arr[mid];
        if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NULL;
}