#include "perfect_numbers.h"
#include <stdint.h>
#include <stdio.h>

int classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 1; // 1 is a divisor for all positive numbers
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            sum += i;
            if (i != number / i) {
                sum += number / i;
            }
        }
    }

    if (sum == number && number != 1) {
        return PERFECT_NUMBER;
    } else if (sum > number) {
        return ABUNDANT_NUMBER;
    } else {
        return DEFICIENT_NUMBER;
    }
}