#include "armstrong_numbers.h"
#include <cmath>
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        int num = input;
        int numDigits = 0;
        int temp = input;
        while (temp > 0) {
            temp /= 10;
            numDigits++;
        }
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            int power = 1;
            for (int i = 0; i < numDigits; ++i) {
                power *= digit;
            }
            sum += power;
            if (sum > input) return false;
            num /= 10;
        }
        return sum == input;
    }
} // namespace armstrong_numbers