#include "perfect_numbers.h"
#include <stdint.h>

int classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 1; 
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            sum += i;
            if (i * i != number) {
                sum += number / i;
            }
        }
    }

    if (sum == number) {
        return PERFECT_NUMBER;
    } else if (sum > number) {
        return ABUNDANT_NUMBER;
    } else {
        return DEFICIENT_NUMBER;
    }
}