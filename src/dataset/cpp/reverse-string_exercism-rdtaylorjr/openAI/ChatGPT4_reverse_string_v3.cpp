#include "reverse_string.h"

namespace reverse_string {

std::string reverse_string(std::string s) {
    size_t left = 0, right = s.length();
    while (left < --right) {
        std::swap(s[left++], s[right]);
    }
    return s;
}

}  // namespace reverse_string