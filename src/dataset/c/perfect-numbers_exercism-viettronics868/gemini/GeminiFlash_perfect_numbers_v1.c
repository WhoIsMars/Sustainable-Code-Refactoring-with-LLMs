#include "perfect_numbers.h"
#include <stdint.h>
#include <math.h>

int classify_number(int number) {
    if (number <= 0) {
        return ERROR;
    }

    int sum = 1; // 1 is always a divisor (except for 1 itself, handled below)
    if (number == 1) return DEFICIENT_NUMBER;

    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            sum += i;
            if (i * i != number) { // Avoid adding the same divisor twice for perfect squares
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