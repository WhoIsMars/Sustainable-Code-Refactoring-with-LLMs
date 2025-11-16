#include "armstrong_numbers.h"
#include <cmath>

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;

    int n = num;
    int exp = 0;
    while (n != 0) {
        n /= 10;
        exp++;
    }

    n = num;
    int sum = 0;
    while (n != 0) {
        int digit = n % 10;
        int power = 1;
        for (int i = 0; i < exp; ++i) {
            power *= digit;
        }
        if (sum > num - power) return false; // Early exit if overflow is possible
        sum += power;
        n /= 10;
    }

    return sum == num;
}

}  // namespace armstrong_numbers