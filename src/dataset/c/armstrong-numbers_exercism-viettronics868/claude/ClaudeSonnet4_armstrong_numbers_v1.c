#include "armstrong_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

void convert_number(int candidate, int *array_number, size_t *leng_of_array){
    int cpy_candidate = candidate;
    size_t index_arr = 0;
    while (cpy_candidate != 0)
    {
        array_number[index_arr] = (cpy_candidate % 10);
        index_arr++;
        cpy_candidate = cpy_candidate / 10;
    }
    *leng_of_array = index_arr;
}

static int int_pow(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

bool is_armstrong_number(int candidate){
    if (candidate < 0) return false;
    
    size_t array_leng = 0;
    int array_of_number[10]; // max digits for 32-bit int
    int sum = 0;
    convert_number(candidate, array_of_number, &array_leng);
    for (size_t i = 0; i < array_leng; i++){
        sum += int_pow(array_of_number[i], array_leng);
    }
    return sum == candidate;
}