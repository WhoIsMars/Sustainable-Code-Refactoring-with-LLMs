#include "binary_search.h"

int *binary_search(int value, const int *arr, size_t length)
{
    int left = 0;
    int right = (int)length - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) >> 1); // Avoid potential overflow
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