#include "armstrong_numbers.h"

#include <math.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;

    int original = candidate;
    int len = 0, temp = candidate;

    // Calculate the number of digits
    while (temp > 0) {
        temp /= 10;
        len++;
    }

    int armstrong_number = 0;
    temp = candidate;

    // Calculate the Armstrong number
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < len; ++i) {
            power *= digit;
        }
        armstrong_number += power;
        temp /= 10;
    }

    return candidate == armstrong_number;
}