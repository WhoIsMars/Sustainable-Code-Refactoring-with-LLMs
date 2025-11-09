#include "trinary.h"
#include <cmath>
namespace trinary
{
    int to_decimal(std::string trinary)
    {
        int decimal = 0;
        int n = static_cast<int>(trinary.length() - 1);
        for (int i = 0; i <= n; i++)
        {
            if(!isdigit(trinary[i]))
                return 0;
            decimal += (trinary[i] - 48) * pow(3, n - i);
        }
        return decimal;
    }
} // namespace trinary
