#include "binary_search.h"

int *binary_search(int value, const int *arr, size_t length)
{
    if (!arr || length == 0) return NULL;
    
    size_t left = 0;
    size_t right = length - 1;
    
    while (left <= right) {
        size_t mid = left + ((right - left) >> 1);
        int mid_val = arr[mid];
        
        if (mid_val == value) {
            return (int *)&arr[mid];
        }
        
        if (mid_val > value) {
            if (mid == 0) break;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return NULL;
}