#include "armstrong_numbers.h"
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;

    int original = candidate, sum = 0, digits[10], num_digits = 0;

    while (candidate > 0) {
        digits[num_digits++] = candidate % 10;
        candidate /= 10;
    }

    for (int i = 0; i < num_digits; i++) {
        int power = 1;
        for (int j = 0; j < num_digits; j++) {
            power *= digits[i];
        }
        sum += power;
    }

    return sum == original;
}