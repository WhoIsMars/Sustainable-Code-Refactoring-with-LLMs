#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdint.h>

static int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

bool is_armstrong_number(int candidate) {
    if (candidate == 0) {
        return true;
    }

    int num_digits = 0;
    int temp = candidate;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }

    int sum = 0;
    temp = candidate;
    while (temp != 0) {
        int digit = temp % 10;
        sum += power(digit, num_digits);
        if (sum > candidate) {
            return false;
        }
        temp /= 10;
    }

    return (sum == candidate);
}