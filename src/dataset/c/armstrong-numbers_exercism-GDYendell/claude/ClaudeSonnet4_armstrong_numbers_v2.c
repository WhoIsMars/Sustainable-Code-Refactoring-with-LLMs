#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;
    
    int original = candidate;
    int len = 0;
    int temp = candidate;
    
    // Count digits
    do {
        len++;
        temp /= 10;
    } while (temp > 0);
    
    // Calculate armstrong sum
    int armstrong_number = 0;
    temp = candidate;
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < len; i++) {
            power *= digit;
        }
        armstrong_number += power;
        temp /= 10;
    }
    
    return original == armstrong_number;
}