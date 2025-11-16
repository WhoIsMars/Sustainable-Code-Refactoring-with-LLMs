#include "binary.h"

#include <string>

namespace binary {

int convert(const std::string& binary_string) {
    int sum = 0;

    for (char ch : binary_string) {
        if (ch != '0' && ch != '1') return 0; // Validate binary input
        sum = (sum << 1) + (ch - '0'); // Use bitwise shift for efficiency
    }

    return sum;
}

}  // namespace binary