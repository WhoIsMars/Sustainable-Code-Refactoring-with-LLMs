#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {
        int out = 0;

        for (char c : num) {
            int nr = c - '0';

            if (nr < 0 || nr > 2) return 0;

            out = out * 3 + nr;
        }
        return out;
    }

}  // namespace trinary