#include <cmath>

#include "armstrong_numbers.h"

namespace armstrong_numbers
{
    bool is_armstrong_number(int num)
    {
        if (num < 0) return false;

        int num_digits = 0, temp = num;
        while (temp > 0)
        {
            ++num_digits;
            temp /= 10;
        }

        int sum = 0, rem = num;
        while (rem > 0)
        {
            int digit = rem % 10;
            int power = 1;
            for (int i = 0; i < num_digits; ++i)
            {
                power *= digit;
            }
            sum += power;
            if (sum > num) return false; // Early exit if sum exceeds num
            rem /= 10;
        }

        return sum == num;
    }
}