#include "armstrong_numbers.h"

static int pow1(int x, int n) {
    if (n == 0) return 1;
    if (x == 0) return 0;
    if (x == 1) return 1;
    
    int res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int digits = 0;
    int temp = candidate;
    
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    int sum = 0;
    temp = candidate;
    
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow1(digit, digits);
        if (sum > candidate) return false;
        temp /= 10;
    }
    
    return sum == candidate;
}