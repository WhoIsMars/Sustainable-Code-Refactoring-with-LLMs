#include "armstrong_numbers.h"
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

void convert_number(int candidate, int *array_number, size_t *leng_of_array) {
    size_t index_arr = 0;
    while (candidate != 0) {
        array_number[index_arr++] = candidate % 10;
        candidate /= 10;
    }
    *leng_of_array = index_arr;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;

    size_t array_leng = 0;
    int array_of_number[10]; // Max digits for int
    int sum = 0, temp = candidate;

    convert_number(candidate, array_of_number, &array_leng);

    for (size_t i = 0; i < array_leng; i++) {
        int digit_pow = 1;
        for (size_t j = 0; j < array_leng; j++) {
            digit_pow *= array_of_number[i];
        }
        sum += digit_pow;
        if (sum > candidate) return false; // Early exit if sum exceeds candidate
    }

    return sum == temp;
}