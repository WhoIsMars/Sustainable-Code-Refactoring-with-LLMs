#include "armstrong_numbers.h"
#include <cmath>
#include <string>

bool armstrong_numbers::is_armstrong_number(const int &num) noexcept {
    if (num < 0) return false;

    int n = num;
    int num_digits = 0;
    while (n != 0) {
        n /= 10;
        num_digits++;
    }

    n = num;
    int sum_digits_raised = 0;
    while (n != 0) {
        int digit = n % 10;
        int power = 1;
        for (int i = 0; i < num_digits; ++i) {
            power *= digit;
        }
        sum_digits_raised += power;
        n /= 10;
    }

    return sum_digits_raised == num;
}