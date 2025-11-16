#include <cmath>

#include "armstrong_numbers.h"

namespace armstrong_numbers
{
    bool is_armstrong_number(int num)
    {
        if (num < 0) return false;

        int n = num;
        int num_digits = 0;
        while (n != 0) {
            n /= 10;
            num_digits++;
        }

        if (num_digits == 0) return true;

        int sum = 0;
        n = num;
        while (n != 0)
        {
            int digit = n % 10;
            int power = 1;
            for (int i = 0; i < num_digits; ++i) {
                if (power > INT_MAX / digit) return false;
                power *= digit;
            }

            if (sum > INT_MAX - power) return false;
            sum += power;
            n /= 10;
        }
        return sum == num;
    }
}