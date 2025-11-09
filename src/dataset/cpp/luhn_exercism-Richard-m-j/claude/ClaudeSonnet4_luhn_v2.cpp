#include "luhn.h"
#include <string>

namespace luhn
{
    bool valid(std::string inputNumber)
    {
        int sum = 0;
        int digitCount = 0;
        bool isSecond = false;
        
        // Process from right to left
        for (int i = static_cast<int>(inputNumber.length()) - 1; i >= 0; i--)
        {
            char c = inputNumber[i];
            
            if (c == ' ')
                continue;
                
            if (c < '0' || c > '9')
                return false;
            
            int digit = c - '0';
            digitCount++;
            
            if (isSecond)
            {
                digit *= 2;
                if (digit > 9)
                    digit -= 9;
            }
            
            sum += digit;
            isSecond = !isSecond;
        }
        
        return digitCount > 1 && sum % 10 == 0;
    }
}