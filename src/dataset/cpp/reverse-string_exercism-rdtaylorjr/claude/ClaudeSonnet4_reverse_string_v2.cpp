#include "reverse_string.h"

namespace reverse_string {

std::string reverse_string(std::string s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        std::swap(s[left], s[right]);
        ++left;
        --right;
    }
    
    return s;
}

}  // namespace reverse_string