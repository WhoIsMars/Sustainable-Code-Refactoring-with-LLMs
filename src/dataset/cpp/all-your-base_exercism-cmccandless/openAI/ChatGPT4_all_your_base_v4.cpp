#include <stdexcept>
#include <vector>

#include "all_your_base.h"

namespace all_your_base
{
    int toDecimalNumber(unsigned int fromBase, const std::vector<unsigned int>& digits)
    {
        int num = 0;
        for (unsigned int digit : digits)
        {
            if (digit >= fromBase) throw std::invalid_argument("Input digits cannot be equal or greater than input base.");
            num = num * fromBase + digit;
        }
        return num;
    }

    std::vector<unsigned int> fromDecimalNumber(unsigned int decimalNumber, unsigned int toBase)
    {
        if (decimalNumber == 0) return {0};
        std::vector<unsigned int> digits;
        while (decimalNumber)
        {
            digits.push_back(decimalNumber % toBase);
            decimalNumber /= toBase;
        }
        std::reverse(digits.begin(), digits.end());
        return digits;
    }

    std::vector<unsigned int> convert(unsigned int fromBase, const std::vector<unsigned int>& digits, unsigned int toBase)
    {
        if (fromBase < 2 || toBase < 2) throw std::invalid_argument("Base must be 2 or greater.");
        return fromDecimalNumber(toDecimalNumber(fromBase, digits), toBase);
    }
} // namespace all_your_base