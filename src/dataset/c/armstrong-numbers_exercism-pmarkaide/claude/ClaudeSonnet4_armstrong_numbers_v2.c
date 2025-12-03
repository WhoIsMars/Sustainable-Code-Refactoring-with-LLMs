#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate)
{
    if (candidate < 0) return false;
    if (candidate < 10) return true;
    
    int num_digits = 0;
    int temp = candidate;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }
    
    int res = 0;
    int num = candidate;
    
    while (num > 0) {
        int digit = num % 10;
        int power = 1;
        for (int i = 0; i < num_digits; i++) {
            power *= digit;
        }
        res += power;
        num /= 10;
    }
    
    return res == candidate;
}