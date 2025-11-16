#include "trinary.h"

namespace trinary
{

    int to_decimal(const std::string _trinary)
    {
        if (_trinary.empty()) {
            return 0;
        }

        int decimal = 0;
        int multiplier = 1;

        for (auto it = _trinary.rbegin(); it != _trinary.rend(); ++it) {
            char digit = *it;
            if (digit < '0' || digit > '2') {
                return 0;
            }
            decimal += (digit - '0') * multiplier;
            multiplier *= 3;
        }

        return decimal;
    }

} // namespace trinary