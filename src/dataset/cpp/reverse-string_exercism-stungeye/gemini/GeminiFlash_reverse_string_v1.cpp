#include "reverse_string.h"
#include <string>

namespace reverse_string {

std::string reverse_string(const std::string& s) {
    size_t n = s.length();
    std::string reversed_s(n, ' '); // Initialize with correct size

    for (size_t i = 0; i < n; ++i) {
        reversed_s[i] = s[n - 1 - i];
    }

    return reversed_s;
}

} // namespace reverse_string