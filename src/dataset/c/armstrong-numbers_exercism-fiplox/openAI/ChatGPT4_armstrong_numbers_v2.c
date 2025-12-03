#include "armstrong_numbers.h"
#include <math.h>

bool is_armstrong_number(int candidate) {
    int sum = 0, copy = candidate, digit_count = 0;

    // Calculate the number of digits
    digit_count = (int)log10(candidate) + 1;

    // Calculate the Armstrong sum
    while (copy > 0) {
        int digit = copy % 10;
        sum += pow(digit, digit_count);
        copy /= 10;
    }

    return sum == candidate;
}