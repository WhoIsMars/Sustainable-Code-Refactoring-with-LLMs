#include "armstrong_numbers.h"
#include <cmath>
#include <string>

bool armstrong_numbers::is_armstrong_number(const int &num) noexcept {
    if (num < 0) return false;

    int sum_digits_raised = 0, temp = num;
    const int num_digits = static_cast<int>(std::log10(num) + 1);

    while (temp > 0) {
        int digit = temp % 10;
        temp /= 10;
        int power = 1;
        for (int i = 0; i < num_digits; ++i) {
            power *= digit;
        }
        sum_digits_raised += power;
        if (sum_digits_raised > num) return false; // Early exit
    }

    return sum_digits_raised == num;
}