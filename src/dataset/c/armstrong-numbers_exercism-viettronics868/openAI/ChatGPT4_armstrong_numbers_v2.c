#include "armstrong_numbers.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;

    int original = candidate;
    int sum = 0;
    int digits[10];
    int num_digits = 0;

    // Extract digits and count them
    while (candidate > 0) {
        digits[num_digits++] = candidate % 10;
        candidate /= 10;
    }

    // Calculate Armstrong sum
    for (int i = 0; i < num_digits; i++) {
        sum += pow(digits[i], num_digits);
        if (sum > original) return false; // Early exit if sum exceeds candidate
    }

    return sum == original;
}