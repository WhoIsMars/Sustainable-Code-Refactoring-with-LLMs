#include "luhn.h"
#include <string>
#include <cctype>

namespace luhn
{
    bool valid(const std::string& inputNumber)
    {
        int sum = 0;
        int digitCount = 0;
        bool doubleDigit = false;

        for (auto it = inputNumber.rbegin(); it != inputNumber.rend(); ++it)
        {
            if (*it == ' ')
                continue;

            if (!std::isdigit(*it))
                return false;

            int digit = *it - '0';
            if (doubleDigit)
            {
                digit *= 2;
                if (digit > 9)
                    digit -= 9;
            }

            sum += digit;
            doubleDigit = !doubleDigit;
            ++digitCount;
        }

        return digitCount > 1 && sum % 10 == 0;
    }
}