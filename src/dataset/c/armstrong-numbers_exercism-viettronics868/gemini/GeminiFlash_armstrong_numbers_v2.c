#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

int get_number_length(int n) {
    int length = 0;
    while (n != 0) {
        n /= 10;
        length++;
    }
    return length;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) {
        return false;
    }

    int num_digits = get_number_length(candidate);
    int original_number = candidate;
    int sum = 0;

    while (original_number != 0) {
        int digit = original_number % 10;
        sum += round(pow(digit, num_digits));
        original_number /= 10;
    }

    return sum == candidate;
}