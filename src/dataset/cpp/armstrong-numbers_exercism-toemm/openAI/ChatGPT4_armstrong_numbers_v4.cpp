#include "armstrong_numbers.h"
#include <cmath>

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;

    int exp = 0, temp = num, sum = 0;
    while (temp > 0) {
        temp /= 10;
        ++exp;
    }

    temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < exp; ++i) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
        if (sum > num) return false; // Early exit if sum exceeds num
    }

    return sum == num;
}

}  // namespace armstrong_numbers