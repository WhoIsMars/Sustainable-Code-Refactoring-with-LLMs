#include "binary_search.h"
#include <stddef.h>
#include <stdio.h>

const int *binary_search(int value, const int *arr, size_t length){
    size_t left = 0;
    size_t right = length;
    
    while (left < right){
        size_t mid = left + (right - left) / 2;
        if (value == arr[mid]){
            return &arr[mid];
        } else if (value < arr[mid]){
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return NULL;
}