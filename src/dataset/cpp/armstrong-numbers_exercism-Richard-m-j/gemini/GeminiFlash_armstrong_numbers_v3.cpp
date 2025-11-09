#include "armstrong_numbers.h"
#include <cmath>
using namespace std;
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        if (input < 0) return false;

        int num = input;
        int numDigits = 0;
        while (num > 0) {
            num /= 10;
            numDigits++;
        }

        num = input;
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            int power = 1;
            for (int i = 0; i < numDigits; ++i) {
                power *= digit;
            }
            if (sum > input - power) return false;
            sum += power;
            num /= 10;
        }

        return sum == input;
    }
} // namespace armstrong_numbers