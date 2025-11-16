#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {

        int out = 0;
        int num_size = num.size();

        for (int i = 0; i < num_size; ++i) {
            char c = num[num_size - 1 - i];
            if (c < '0' || c > '2') {
                return 0;
            }
            int digit = c - '0';
            out += digit * static_cast<int>(std::pow(3.0, i));
        }
        return out;
    }

}  // namespace trinary