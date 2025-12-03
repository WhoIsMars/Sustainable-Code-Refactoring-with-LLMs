#include "armstrong_numbers.h"

#include <stdio.h>
#include <stdint.h>

bool is_armstrong_number(int candidate)
{
    if (candidate < 0) {
        return false;
    }
    
    if (candidate == 0) {
        return true;
    }

    int temp = candidate;
    int exponent = 0;
    
    while (temp > 0) {
        exponent++;
        temp /= 10;
    }

    int sum = 0;
    temp = candidate;

    while (temp > 0) {
        int digit = temp % 10;
        
        int digit_power = 1;
        for (int i = 0; i < exponent; i++) {
            digit_power *= digit;
        }
        
        sum += digit_power;
        temp /= 10;

        if (sum > candidate) {
            return false;
        }
    }

    return (sum == candidate);
}