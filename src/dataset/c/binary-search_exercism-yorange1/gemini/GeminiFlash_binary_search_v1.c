#include "binary_search.h"
#include <stddef.h>

int *binary_search(int value, const int *arr, size_t length)
{
    if (arr == NULL || length == 0) {
        return NULL;
    }

    size_t left = 0;
    size_t right = length - 1;

    while (left <= right)
    {
        size_t mid = left + (right - left) / 2; // Prevent potential overflow
        if (arr[mid] == value)
        {
            return (int *)&arr[mid];
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return NULL;
}