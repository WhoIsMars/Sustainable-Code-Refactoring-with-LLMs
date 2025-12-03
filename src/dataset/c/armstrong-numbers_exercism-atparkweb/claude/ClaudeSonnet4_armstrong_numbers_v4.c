#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int original = candidate;
    int numDigits = 0;
    int temp = candidate;
    
    while (temp > 0) {
        temp /= 10;
        numDigits++;
    }
    
    int total = 0;
    temp = candidate;
    
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < numDigits; i++) {
            power *= digit;
        }
        total += power;
        temp /= 10;
    }
    
    return original == total;
}