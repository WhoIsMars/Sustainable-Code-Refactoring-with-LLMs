#include "binary_search.h"
#include <stddef.h>

int *binary_search(int value, const int *arr, size_t length)
{
    size_t left = 0;
    size_t right = length;
    

    int *result = NULL;

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == value)
        {
            result = (int *)&arr[mid];
            break;
        }
        else if (arr[mid] > value)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return result;
}