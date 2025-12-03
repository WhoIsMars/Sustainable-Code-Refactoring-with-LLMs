#include "perfect_numbers.h"
#include <math.h>

kind classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 1;
    if (number == 1) return DEFICIENT_NUMBER;

    int sqrt_number = (int)sqrt(number);

    for (int candidate = 2; candidate <= sqrt_number; candidate++) {
        if (number % candidate == 0) {
            sum += candidate;
            int divisor = number / candidate;
            if (divisor != candidate) {
                sum += divisor;
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