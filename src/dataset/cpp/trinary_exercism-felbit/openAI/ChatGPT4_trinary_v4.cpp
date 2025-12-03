#include "trinary.h"
#include <cctype>

namespace trinary
{

    int to_decimal(const std::string& _trinary)
    {
        int _decimal = 0;
        int _multiplier = 1;

        for (auto it = _trinary.rbegin(); it != _trinary.rend(); ++it)
        {
            if (*it < '0' || *it > '2') return 0;
            _decimal += (*it - '0') * _multiplier;
            _multiplier *= 3;
        }

        return _decimal;
    }

} // namespace trinary