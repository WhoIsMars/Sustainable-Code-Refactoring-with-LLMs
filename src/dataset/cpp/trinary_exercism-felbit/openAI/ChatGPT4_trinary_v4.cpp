#include "trinary.h"
#include <cctype>

namespace trinary
{

    int to_decimal(const std::string& _trinary)
    {
        int _decimal = 0;
        for (char c : _trinary)
        {
            if (c < '0' || c > '2') return 0;
            _decimal = _decimal * 3 + (c - '0');
        }
        return _decimal;
    }

} // namespace trinary