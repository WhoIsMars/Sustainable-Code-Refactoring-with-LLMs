#include "trinary.h"
#include <cctype>

namespace trinary {
    int to_decimal(std::string trinary) {
        int decimal = 0;
        for (char c : trinary) {
            if (!isdigit(c)) {
                return 0;
            }
            int digit = c - '0';
            if (digit > 2) {
                return 0;
            }
            decimal = decimal * 3 + digit;
        }
        return decimal;
    }
} // namespace trinary