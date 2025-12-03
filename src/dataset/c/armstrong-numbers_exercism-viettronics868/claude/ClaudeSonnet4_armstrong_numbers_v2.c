#include "armstrong_numbers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static int int_pow(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int temp = candidate;
    int digits = 0;
    
    // Count digits
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    temp = candidate;
    int sum = 0;
    
    // Calculate sum of powers
    while (temp > 0) {
        int digit = temp % 10;
        sum += int_pow(digit, digits);
        temp /= 10;
    }
    
    return sum == candidate;
}