#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {

        int out = 0;
        int num_size = num.size();

        for (int i = 0; i < num_size; ++i) {
            char c = num[i];
            if (c < '0' || c > '2') {
                return 0;
            }

            int digit = c - '0';
            out = out * 3 + digit;
        }

        return out;
    }

}  // namespace trinary