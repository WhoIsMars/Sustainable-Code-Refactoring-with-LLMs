#include "armstrong_numbers.h"

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;
    if (num < 10) return true;
    
    int original = num;
    int digit_count = 0;
    int temp = num;
    
    while (temp > 0) {
        ++digit_count;
        temp /= 10;
    }
    
    int sum = 0;
    temp = num;
    
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < digit_count; ++i) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
    }
    
    return sum == original;
}

}  // namespace armstrong_numbers