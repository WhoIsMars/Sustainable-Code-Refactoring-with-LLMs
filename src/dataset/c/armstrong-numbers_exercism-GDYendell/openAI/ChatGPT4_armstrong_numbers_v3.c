#include "armstrong_numbers.h"

#include <math.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
    int original = candidate;
    int armstrong_number = 0;
    int len = 0;

    // Calculate the number of digits
    for (int temp = candidate; temp > 0; temp /= 10) {
        len++;
    }

    // Calculate the Armstrong number
    for (int temp = candidate; temp > 0; temp /= 10) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < len; ++i) {
            power *= digit;
        }
        armstrong_number += power;
    }

    return candidate == armstrong_number;
}