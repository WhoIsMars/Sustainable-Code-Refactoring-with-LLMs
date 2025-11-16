#include "armstrong_numbers.h"
#include <cmath>

bool armstrong_numbers::is_armstrong_number(const int &num) noexcept {
    if (num < 0) return false;

    int sum_digits_raised = 0, temp = num, num_digits = 0;

    // Calculate the number of digits
    while (temp) {
        ++num_digits;
        temp /= 10;
    }

    temp = num;
    // Calculate the sum of digits raised to the power of num_digits
    while (temp) {
        int digit = temp % 10;
        sum_digits_raised += static_cast<int>(std::pow(digit, num_digits));
        temp /= 10;
    }

    return sum_digits_raised == num;
}