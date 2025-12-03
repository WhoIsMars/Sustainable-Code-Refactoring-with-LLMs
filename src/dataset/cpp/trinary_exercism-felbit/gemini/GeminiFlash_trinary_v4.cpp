#include "trinary.h"
#include <algorithm>
#include <cctype>

namespace trinary
{

    int to_decimal(const std::string _trinary)
    {
        int _decimal = 0;
        int _multiplier = 1;

        for (auto it = _trinary.rbegin(); it != _trinary.rend(); ++it)
        {
            if (!std::isdigit(*it)) {
                return 0;
            }

            int digit = *it - '0';

            if (digit < 0 || digit > 2)
            {
                return 0;
            }

            _decimal += digit * _multiplier;
            _multiplier *= 3;
        }

        return _decimal;
    }

} // namespace trinary