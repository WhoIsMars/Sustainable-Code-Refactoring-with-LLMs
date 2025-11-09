#include "trinary.h"
#include <algorithm>

namespace trinary {
    int to_decimal(std::string trinary) {
        int decimal = 0;
        int n = static_cast<int>(trinary.length());

        for (int i = 0; i < n; ++i) {
            char c = trinary[i];
            if (c < '0' || c > '2') {
                return 0;
            }
            decimal = decimal * 3 + (c - '0');
        }
        return decimal;
    }
} // namespace trinary