#include "armstrong_numbers.h"
#include <cmath>
using namespace std;
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        int num = input;
        int numDigits = 0;
        for (; num > 0; num /= 10)
            numDigits++;
        num = input;
        int sum = 0;
        for (; num > 0; num /= 10)
            sum += pow(num % 10, numDigits);
        if (sum == input)
            return true;
        else
            return false;
    }
} // namespace armstrong_numbers
