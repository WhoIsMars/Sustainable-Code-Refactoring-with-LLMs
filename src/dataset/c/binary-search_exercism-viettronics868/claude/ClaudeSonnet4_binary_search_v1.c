#include "binary_search.h"
#include <stddef.h>
#include <stdio.h>

const int *binary_search(int value, const int *arr, size_t length){
    if (length == 0) return NULL;
    
    size_t left = 0;
    size_t right = length - 1;
    
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        
        if (arr[mid] == value) {
            return &arr[mid];
        } else if (value < arr[mid]) {
            if (mid == 0) break;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return NULL;
}