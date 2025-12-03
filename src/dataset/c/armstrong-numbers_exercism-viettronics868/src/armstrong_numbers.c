#include "armstrong_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

void convert_number(int candidate, int *array_number, size_t *leng_of_array){
    int cpy_array_number[32];
    int cpy_candidate = candidate;
    size_t index_arr = 0;
    while (cpy_candidate != 0)
    {
        cpy_array_number[index_arr] = (cpy_candidate % 10);
        index_arr++;
        cpy_candidate = cpy_candidate / 10;
    }
    *leng_of_array = index_arr;
    memcpy(array_number, cpy_array_number,(sizeof(cpy_array_number))/(sizeof(cpy_array_number[0])));

}

bool is_armstrong_number(int candidate){
    size_t array_leng = 0;
    int array_of_number[32];
    int sum = 0;
    convert_number(candidate, array_of_number, &array_leng);
    for (size_t i = 0; i < array_leng; i++){
        sum += pow(array_of_number[i], array_leng);
    }
    if (sum == candidate){
        return 1;
    }else{
        return 0;
    }
}