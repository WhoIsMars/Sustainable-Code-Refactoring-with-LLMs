#include "trinary.h"
#include <algorithm>
#include <stdexcept>

namespace trinary
{

    int to_decimal(const std::string trinary_str)
    {
        int decimal = 0;
        int n = trinary_str.length();

        for (int i = 0; i < n; ++i) {
            char c = trinary_str[i];
            if (c < '0' || c > '2') {
                return 0;
            }
            decimal = decimal * 3 + (c - '0');
        }

        return decimal;
    }

} // namespace trinary