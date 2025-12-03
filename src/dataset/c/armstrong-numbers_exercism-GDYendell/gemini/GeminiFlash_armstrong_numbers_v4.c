#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdio.h>
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
        return candidate == 0;
    }

    int armstrong_sum = 0;
    temp = candidate;
    while (temp != 0) {
        int digit = temp % 10;
        double power = 1.0;
        for (int i = 0; i < num_digits; ++i) {
            power *= digit;
        }

        if (power > (double)__INT_MAX__ - armstrong_sum) {
            return false;
        }

        armstrong_sum += (int)power;
        temp /= 10;
    }

    return candidate == armstrong_sum;
}