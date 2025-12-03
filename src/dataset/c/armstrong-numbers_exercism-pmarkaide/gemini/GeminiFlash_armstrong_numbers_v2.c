#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdio.h>

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) {
        return false;
    }

    int num = candidate;
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
        temp /= 10;
        if (sum > candidate) return false;
    }

    return sum == candidate;
}