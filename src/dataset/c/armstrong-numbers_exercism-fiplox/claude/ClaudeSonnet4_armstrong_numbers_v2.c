#include "armstrong_numbers.h"

static int pow1(int base, int exp) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    
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
    
    int digits = 0;
    int temp = candidate;
    
    // Count digits using bit operations when possible
    while (temp > 0) {
        temp /= 10;
        digits++;
    }
    
    int sum = 0;
    temp = candidate;
    
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow1(digit, digits);
        temp /= 10;
    }
    
    return sum == candidate;
}