#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>

int classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 0;
    for (int i = 1; i <= number / 2; i++) {
        if (number % i == 0) {
            sum += i;
            if (sum > number) {
                return ABUNDANT_NUMBER;
            }
        }
    }

    if (sum == number) {
        return PERFECT_NUMBER;
    } else {
        return DEFICIENT_NUMBER;
    }
}