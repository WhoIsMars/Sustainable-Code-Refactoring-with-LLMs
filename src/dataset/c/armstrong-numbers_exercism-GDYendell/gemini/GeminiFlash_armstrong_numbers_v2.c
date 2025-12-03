#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdio.h>  // Included for debugging purposes, remove in production
#include <math.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0) {
        return false;
    }

    int num_digits = 0;
    int temp = candidate;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }

    if (num_digits == 0) {
        return true; // Consider 0 an Armstrong number
    }

    int armstrong_sum = 0;
    temp = candidate;
    while (temp != 0) {
        int digit = temp % 10;
        armstrong_sum += (int)round(pow(digit, num_digits));  // Explicit cast and rounding
        temp /= 10;
    }

    return armstrong_sum == candidate;
}