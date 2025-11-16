#include "armstrong_numbers.h"
#include <cmath>

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;

    int exp = 0, temp = num, sum = 0;
    while (temp) {
        ++exp;
        temp /= 10;
    }

    temp = num;
    while (temp) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < exp; ++i) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
    }

    return sum == num;
}

}  // namespace armstrong_numbers