#include "armstrong_numbers.h"
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
        
        // Calculate sum using integer exponentiation
        while (num > 0) {
            int digit = num % 10;
            long long digitPower = 1;
            for (int i = 0; i < numDigits; i++) {
                digitPower *= digit;
            }
            sum += digitPower;
            num /= 10;
            
            // Early exit if sum exceeds input
            if (sum > input) return false;
        }
        
        return sum == input;
    }
}