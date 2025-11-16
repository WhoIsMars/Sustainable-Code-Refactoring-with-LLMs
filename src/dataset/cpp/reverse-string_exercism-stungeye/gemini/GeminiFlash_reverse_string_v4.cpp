#include "reverse_string.h"
#include <algorithm>
#include <string>

namespace reverse_string {

std::string reverse_string(const std::string& s) {
    std::string reversed_s;
    reversed_s.reserve(s.size());
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        reversed_s.push_back(*it);
    }
    return reversed_s;
}

} // namespace reverse_string