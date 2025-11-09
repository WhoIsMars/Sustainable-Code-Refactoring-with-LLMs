#include "armstrong_numbers.h"
#include <cmath>
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        int num = input;
        int numDigits = 0;
        int digits[10]; // Array to store digits
        while (num > 0)
        {
            digits[numDigits++] = num % 10;
            num /= 10;
        }
        int sum = 0;
        for (int i = 0; i < numDigits; ++i)
        {
            int power = 1;
            for (int j = 0; j < numDigits; ++j)
                power *= digits[i];
            sum += power;
            if (sum > input) // Early exit if sum exceeds input
                return false;
        }
        return sum == input;
    }
} // namespace armstrong_numbers