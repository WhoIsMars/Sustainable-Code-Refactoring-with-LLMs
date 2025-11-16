#include "armstrong_numbers.h"
#include <cmath>
#include <string>

bool armstrong_numbers::is_armstrong_number(const int &num) noexcept {
    if (num < 0) {
        return false;
    }

    int temp_num = num;
    int num_digits = 0;
    while (temp_num != 0) {
        temp_num /= 10;
        num_digits++;
    }

    temp_num = num;
    int sum_digits_raised = 0;
    while (temp_num != 0) {
        int digit = temp_num % 10;
        temp_num /= 10;

        int digit_raised = 1;
        for (int i = 0; i < num_digits; ++i) {
            digit_raised *= digit;
        }
        sum_digits_raised += digit_raised;
    }

    return sum_digits_raised == num;
}