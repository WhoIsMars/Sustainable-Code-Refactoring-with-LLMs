#include "armstrong_numbers.h"
#include <cmath>
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        int num = input;
        int numDigits = static_cast<int>(log10(num) + 1);
        int sum = 0;
        while (num > 0)
        {
            int digit = num % 10;
            int power = 1;
            for (int i = 0; i < numDigits; ++i)
                power *= digit;
            sum += power;
            if (sum > input) // Early exit if sum exceeds input
                return false;
            num /= 10;
        }
        return sum == input;
    }
} // namespace armstrong_numbers