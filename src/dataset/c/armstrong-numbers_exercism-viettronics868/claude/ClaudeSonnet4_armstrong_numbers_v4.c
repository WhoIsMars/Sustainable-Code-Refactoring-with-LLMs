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
    
    while (cpy_candidate != 0) {
        array_number[index_arr] = cpy_candidate % 10;
        index_arr++;
        cpy_candidate /= 10;
    }
    *leng_of_array = index_arr;
}

bool is_armstrong_number(int candidate){
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int digits[10];
    size_t num_digits = 0;
    int temp = candidate;
    
    while (temp > 0) {
        digits[num_digits] = temp % 10;
        num_digits++;
        temp /= 10;
    }
    
    int sum = 0;
    for (size_t i = 0; i < num_digits; i++) {
        int power = 1;
        for (size_t j = 0; j < num_digits; j++) {
            power *= digits[i];
        }
        sum += power;
        if (sum > candidate) return false;
    }
    
    return sum == candidate;
}