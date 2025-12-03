#include "trinary.h"
#include <algorithm>
#include <stdexcept>

namespace trinary
{

    int to_decimal(const std::string _trinary)
    {
        int _decimal = 0;
        int _multiplier = 1;

        for (auto it = _trinary.rbegin(); it != _trinary.rend(); ++it)
        {
            if (*it < '0' || *it > '2')
            {
                return 0;
            }

            int digit = *it - '0';
            _decimal += digit * _multiplier;
            _multiplier *= 3;
        }

        return _decimal;
    }

} // namespace trinary