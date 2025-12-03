#include "binary_search.h"



const int *binary_search(int value, const int *arr, size_t length) {
    int a, b, m;
    a = 0;
    b = length - 1;
    while (a <= b) {
        m = (a + b) / 2;
        if (arr[m] == value) {
            return &arr[m];
        }
        if (arr[m] < value) {
            a = m + 1;
        } else {
            b = m - 1;
        }
    }

    return NULL;
}
