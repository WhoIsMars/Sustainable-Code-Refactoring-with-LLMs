#include "armstrong_numbers.h"

namespace armstrong_numbers
{
    bool is_armstrong_number(int num)
    {
        if (num <= 0) return false;
        
        int original = num;
        int num_digits = 0;
        int temp = num;
        
        while (temp > 0) {
            ++num_digits;
            temp /= 10;
        }
        
        int sum = 0;
        temp = num;
        
        while (temp > 0) {
            int digit = temp % 10;
            int power = 1;
            for (int i = 0; i < num_digits; ++i) {
                power *= digit;
            }
            sum += power;
            temp /= 10;
        }
        
        return sum == original;
    }
}