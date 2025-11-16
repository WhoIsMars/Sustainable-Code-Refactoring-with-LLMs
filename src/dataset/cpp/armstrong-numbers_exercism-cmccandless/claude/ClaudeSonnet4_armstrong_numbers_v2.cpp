#include "armstrong_numbers.h"

namespace armstrong_numbers
{
    bool is_armstrong_number(int num)
    {
        if (num < 0) return false;
        if (num < 10) return true;
        
        int original = num;
        int num_digits = 0;
        int temp = num;
        
        // Count digits without floating point operations
        while (temp > 0) {
            num_digits++;
            temp /= 10;
        }
        
        int sum = 0;
        temp = num;
        
        // Calculate sum using integer operations only
        while (temp > 0) {
            int digit = temp % 10;
            int power = 1;
            for (int i = 0; i < num_digits; i++) {
                power *= digit;
            }
            sum += power;
            temp /= 10;
        }
        
        return sum == original;
    }
}