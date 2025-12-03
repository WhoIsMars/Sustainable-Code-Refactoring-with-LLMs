#include "luhn.h"
#include <string>
#include <cctype>

namespace luhn
{
    bool valid(const std::string& inputNumber)
    {
        int sum = 0;
        int count = 0;

        for (auto it = inputNumber.rbegin(); it != inputNumber.rend(); ++it)
        {
            if (*it == ' ')
                continue;

            if (!isdigit(*it))
                return false;

            int digit = *it - '0';
            if (count % 2 == 1)
            {
                digit *= 2;
                if (digit > 9)
                    digit -= 9;
            }

            sum += digit;
            ++count;
        }

        return count > 1 && sum % 10 == 0;
    }
}