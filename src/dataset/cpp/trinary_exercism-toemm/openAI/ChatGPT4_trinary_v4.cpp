#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {
        int out = 0;

        for (char c : num) {
            if (c < '0' || c > '2') return 0;
            out = out * 3 + (c - '0');
        }

        return out;
    }

}  // namespace trinary