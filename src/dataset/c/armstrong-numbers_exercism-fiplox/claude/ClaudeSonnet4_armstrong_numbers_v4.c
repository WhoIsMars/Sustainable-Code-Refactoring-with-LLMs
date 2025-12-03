#include "armstrong_numbers.h"

static int pow1(int x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    
    int result = 1;
    while (n > 0) {
        if (n & 1) {
            result *= x;
        }
        x *= x;
        n >>= 1;
    }
    return result;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int temp = candidate;
    int digits = 0;
    
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    temp = candidate;
    int sum = 0;
    
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow1(digit, digits);
        temp /= 10;
    }
    
    return sum == candidate;
}