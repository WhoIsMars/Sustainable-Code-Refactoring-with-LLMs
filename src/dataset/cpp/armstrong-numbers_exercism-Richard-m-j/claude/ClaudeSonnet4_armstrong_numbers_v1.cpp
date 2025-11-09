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
        
        // Count digits
        while (num > 0) {
            num /= 10;
            numDigits++;
        }
        
        num = input;
        long long sum = 0;
        
        // Calculate sum of powers
        while (num > 0) {
            int digit = num % 10;
            sum += static_cast<long long>(pow(digit, numDigits));
            num /= 10;
        }
        
        return sum == input;
    }
} // namespace armstrong_numbers