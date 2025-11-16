#include "armstrong_numbers.h"
#include <cmath>

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
    if (num < 0) return false;

    int exp = 0, temp = num, sum = 0;
    int digits[10] = {};

    // Calculate the number of digits and store each digit
    while (temp > 0) {
        digits[exp++] = temp % 10;
        temp /= 10;
    }

    // Calculate the Armstrong sum
    for (int i = 0; i < exp; ++i) {
        int digit_pow = 1;
        for (int j = 0; j < exp; ++j) {
            digit_pow *= digits[i];
        }
        sum += digit_pow;
        if (sum > num) return false; // Early exit if sum exceeds num
    }

    return sum == num;
}

}  // namespace armstrong_numbers