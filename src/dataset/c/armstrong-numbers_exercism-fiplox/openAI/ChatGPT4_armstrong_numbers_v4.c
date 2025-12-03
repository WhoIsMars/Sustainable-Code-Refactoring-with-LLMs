#include "armstrong_numbers.h"
#include <math.h>

bool is_armstrong_number(int candidate) {
    int sum = 0, copy = candidate, digits = 0, power_lookup[10];

    while (copy > 0) {
        digits++;
        copy /= 10;
    }

    for (int i = 0; i < 10; i++) {
        power_lookup[i] = (int)pow(i, digits);
    }

    copy = candidate;
    while (copy > 0) {
        sum += power_lookup[copy % 10];
        copy /= 10;
    }

    return sum == candidate;
}