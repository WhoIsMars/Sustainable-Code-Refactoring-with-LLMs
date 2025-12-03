#include "trinary.h"
#include <algorithm>
#include <cctype>

namespace trinary
{

    int to_decimal(const std::string _trinary)
    {
        int decimal = 0;
        int n = _trinary.length();

        for (int i = 0; i < n; ++i) {
            if (!std::isdigit(_trinary[i]) || _trinary[i] > '2') {
                return 0;
            }
        }

        for (int i = 0; i < n; ++i) {
            decimal = decimal * 3 + (_trinary[i] - '0');
        }

        return decimal;
    }

} // namespace trinary