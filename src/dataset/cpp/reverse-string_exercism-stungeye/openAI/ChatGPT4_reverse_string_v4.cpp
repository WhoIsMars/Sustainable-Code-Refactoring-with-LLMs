#include "reverse_string.h"

namespace reverse_string {
    std::string reverse_string(const std::string& s) {
        std::string reversed;
        reversed.reserve(s.size());
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            reversed.push_back(*it);
        }
        return reversed;
    }
} // namespace reverse_string