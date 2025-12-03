#include "binary_search.h"
#include <stddef.h>
#include <stdio.h>

const int *binary_search(int value, const int *arr, size_t length){
    const int *left = arr;
    const int *right = arr + length;
    
    while (left < right) {
        const int *mid = left + ((right - left) >> 1);
        
        if (value == *mid) {
            return mid;
        } else if (value < *mid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return NULL;
}