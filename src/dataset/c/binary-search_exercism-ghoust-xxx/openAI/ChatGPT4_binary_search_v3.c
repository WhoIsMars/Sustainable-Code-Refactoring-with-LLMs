#include "binary_search.h"

const int *binary_search(int value, const int *arr, size_t length) {
    size_t a = 0, b = length;
    while (a < b) {
        size_t m = a + (b - a) / 2;
        if (arr[m] == value) {
            return &arr[m];
        } else if (arr[m] < value) {
            a = m + 1;
        } else {
            b = m;
        }
    }
    return NULL;
}