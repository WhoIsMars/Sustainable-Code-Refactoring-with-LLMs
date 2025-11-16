#include "reverse_string.h"

namespace reverse_string {
    // Use move semantics to avoid unnecessary copies and improve efficiency.
    std::string reverse_string(std::string s) {
        std::reverse(s.begin(), s.end());
        return std::move(s);
    }
} // namespace reverse_string