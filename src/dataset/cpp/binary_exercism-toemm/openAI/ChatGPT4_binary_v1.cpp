#include "binary.h"

#include <string>

namespace binary {

int convert(std::string binary_string) {
    int sum = 0;
    int base = 1;

    for (auto it = binary_string.rbegin(); it != binary_string.rend(); ++it) {
        char ch = *it;
        int nr = ch - '0';

        // Abort if anything is non-digit
        if (nr < 0 || nr > 1) return 0;

        sum += nr * base;
        base <<= 1; // Efficiently multiply base by 2
    }

    return sum;
}

}  // namespace binary