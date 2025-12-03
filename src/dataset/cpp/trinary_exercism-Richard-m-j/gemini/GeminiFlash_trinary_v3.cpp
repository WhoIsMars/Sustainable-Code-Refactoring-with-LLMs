#include "trinary.h"
#include <algorithm>
#include <cctype>

namespace trinary {
    int to_decimal(std::string trinary) {
        int decimal = 0;
        int n = static_cast<int>(trinary.length());

        for (int i = 0; i < n; ++i) {
            if (!isdigit(trinary[i])) {
                return 0;
            }
            int digit = trinary[i] - '0';
            if (digit < 0 || digit > 2) return 0;

            decimal = decimal * 3 + digit;
        }
        return decimal;
    }
} // namespace trinary