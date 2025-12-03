#include "armstrong_numbers.h"

#include <math.h>

bool is_armstrong_number(int candidate) {
    int original = candidate, armstrong_number = 0, len = 0, temp = candidate;

    while (temp > 0) {
        temp /= 10;
        len++;
    }

    temp = candidate;
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < len; i++) {
            power *= digit;
        }
        armstrong_number += power;
        temp /= 10;
    }

    return candidate == armstrong_number;
}