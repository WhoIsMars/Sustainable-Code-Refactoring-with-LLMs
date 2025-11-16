#include "armstrong_numbers.h"

bool armstrong_numbers::is_armstrong_number(const int &num) noexcept {
    if (num < 0) return false;
    if (num < 10) return true;
    
    int temp = num;
    int num_digits = 0;
    
    while (temp > 0) {
        ++num_digits;
        temp /= 10;
    }
    
    temp = num;
    int sum_digits_raised = 0;
    
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < num_digits; ++i) {
            power *= digit;
        }
        sum_digits_raised += power;
        temp /= 10;
    }
    
    return sum_digits_raised == num;
}