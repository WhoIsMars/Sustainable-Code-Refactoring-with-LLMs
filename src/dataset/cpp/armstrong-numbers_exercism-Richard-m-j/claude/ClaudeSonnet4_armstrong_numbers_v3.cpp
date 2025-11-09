#include "armstrong_numbers.h"
#include <cmath>
using namespace std;
namespace armstrong_numbers
{
    bool is_armstrong_number(int input)
    {
        if (input < 0) return false;
        if (input < 10) return true;
        
        int num = input;
        int numDigits = 0;
        while (num > 0) {
            num /= 10;
            ++numDigits;
        }
        
        num = input;
        long long sum = 0;
        while (num > 0) {
            int digit = num % 10;
            long long digitPower = 1;
            for (int i = 0; i < numDigits; ++i) {
                digitPower *= digit;
            }
            sum += digitPower;
            if (sum > input) return false;
            num /= 10;
        }
        
        return sum == input;
    }
}