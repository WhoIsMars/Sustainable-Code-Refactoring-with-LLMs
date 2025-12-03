#include "binary_search.h"
#include <stddef.h>
#include <stdio.h>


const int *binary_search(int value, const int *arr, size_t length){

    int *cpy_arr = (int *)arr;
    while (length != 0){
        size_t half_leng = length / 2;
        if (value == cpy_arr[half_leng]){
            cpy_arr = cpy_arr + half_leng;
            return cpy_arr;
        } else if ( value < cpy_arr[half_leng])
        {
            length = half_leng;
        } else{
            cpy_arr = cpy_arr + half_leng + 1;
            length = half_leng;
        }
    }
    return NULL;
    
}