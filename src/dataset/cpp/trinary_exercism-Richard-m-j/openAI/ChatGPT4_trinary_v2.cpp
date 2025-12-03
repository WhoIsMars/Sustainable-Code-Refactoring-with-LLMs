#include "trinary.h"
#include <cctype>
namespace trinary
{
    int to_decimal(const std::string& trinary)
    {
        int decimal = 0;
        for (char c : trinary)
        {
            if (!std::isdigit(c))
                return 0;
            decimal = decimal * 3 + (c - '0');
        }
        return decimal;
    }
} // namespace trinary