#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdint.h>

static unsigned int power(int base, int exp) {
    unsigned int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) {
        return false;
    }

    if (candidate == 0) {
        return true;
    }

    int temp = candidate;
    int exponent = 0;
    while (temp != 0) {
        exponent++;
        temp /= 10;
    }

    temp = candidate;
    unsigned int sum = 0;

    while (temp != 0) {
        int digit = temp % 10;
        sum += power(digit, exponent);
        if (sum > candidate) {
            return false;
        }
        temp /= 10;
    }

    return (sum == candidate);
}