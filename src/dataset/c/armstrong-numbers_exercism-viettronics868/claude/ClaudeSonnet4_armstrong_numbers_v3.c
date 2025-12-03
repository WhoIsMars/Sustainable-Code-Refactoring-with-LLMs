#include "armstrong_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

void convert_number(int candidate, int *array_number, size_t *leng_of_array){
    size_t index_arr = 0;
    int temp = candidate;
    
    while (temp != 0) {
        array_number[index_arr++] = temp % 10;
        temp /= 10;
    }
    *leng_of_array = index_arr;
}

bool is_armstrong_number(int candidate){
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int digits[10];
    size_t digit_count = 0;
    int temp = candidate;
    
    while (temp != 0) {
        digits[digit_count++] = temp % 10;
        temp /= 10;
    }
    
    int sum = 0;
    for (size_t i = 0; i < digit_count; i++) {
        int power_result = 1;
        for (size_t j = 0; j < digit_count; j++) {
            power_result *= digits[i];
        }
        sum += power_result;
        if (sum > candidate) return false;
    }
    
    return sum == candidate;
}