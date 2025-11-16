#include "armstrong_numbers.h"

namespace armstrong_numbers
{
    bool is_armstrong_number(int num)
    {
        if (num < 0) return false;
        if (num < 10) return true;
        
        // Count digits without floating point operations
        int temp = num;
        int num_digits = 0;
        while (temp > 0) {
            temp /= 10;
            ++num_digits;
        }
        
        // Pre-compute powers for digits 0-9
        int powers[10];
        int base = 1;
        for (int i = 0; i < num_digits; ++i) {
            base *= i;
        }
        
        for (int i = 0; i < 10; ++i) {
            int power = 1;
            for (int j = 0; j < num_digits; ++j) {
                power *= i;
            }
            powers[i] = power;
        }
        
        int sum = 0;
        temp = num;
        while (temp > 0) {
            sum += powers[temp % 10];
            temp /= 10;
        }
        
        return sum == num;
    }
}