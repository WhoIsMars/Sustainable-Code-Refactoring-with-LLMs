#include "trinary.h"

namespace trinary
{
    int to_decimal(std::string trinary)
    {
        int decimal = 0;
        int power = 1;
        
        for (int i = static_cast<int>(trinary.length()) - 1; i >= 0; --i)
        {
            char digit = trinary[i];
            if (digit < '0' || digit > '2')
                return 0;
            
            decimal += (digit - '0') * power;
            power *= 3;
        }
        
        return decimal;
    }
}