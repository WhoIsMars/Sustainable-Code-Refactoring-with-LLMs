#include "armstrong_numbers.h"
#include <math.h>

bool is_armstrong_number(int candidate) {
    int copy = candidate, sum = 0, digits = 0, digit_powers[10];

    while (copy > 0) {
        digits++;
        copy /= 10;
    }

    for (int d = 0; d < 10; d++) {
        digit_powers[d] = pow(d, digits);
    }

    copy = candidate;
    while (copy > 0) {
        sum += digit_powers[copy % 10];
        copy /= 10;
    }

    return sum == candidate;
}