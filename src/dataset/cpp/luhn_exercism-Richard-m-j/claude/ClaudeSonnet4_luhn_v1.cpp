#include "luhn.h"
#include <string>
#include <cctype>

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
                
            if (!std::isdigit(c))
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