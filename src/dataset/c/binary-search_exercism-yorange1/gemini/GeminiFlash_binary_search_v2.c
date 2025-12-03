#include "binary_search.h"
#include <stddef.h>

int *binary_search(int value, const int *arr, size_t length) {
    size_t left = 0;
    size_t right = length;

    while (left < right) {
        size_t mid = left + (right - left) / 2;  // Prevent potential overflow
        if (arr[mid] == value) {
            return (int *)&arr[mid];
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return NULL;
}