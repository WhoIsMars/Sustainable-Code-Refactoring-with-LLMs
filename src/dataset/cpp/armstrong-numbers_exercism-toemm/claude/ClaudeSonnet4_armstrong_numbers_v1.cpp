#include "armstrong_numbers.h"

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;
    if (num < 10) return true;
    
    int original = num;
    int exp = 0;
    int temp = num;
    
    // Count digits without floating point operations
    while (temp > 0) {
        exp++;
        temp /= 10;
    }
    
    int sum = 0;
    temp = num;
    
    // Use integer arithmetic instead of pow
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < exp; i++) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
    }
    
    return sum == original;
}

}  // namespace armstrong_numbers