#include "perfect_numbers.h"
#include <math.h>

int classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 1; 
    if (number == 1) return DEFICIENT_NUMBER;

    for (int i = 2; i <= sqrt(number); i++) {
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