#include "reverse_string.h"

namespace reverse_string {

std::string reverse_string(std::string s) {
    size_t n = s.size();
    for (size_t i = 0; i < n / 2; ++i) {
        std::swap(s[i], s[n - i - 1]);
    }
    return s;
}

}  // namespace reverse_string