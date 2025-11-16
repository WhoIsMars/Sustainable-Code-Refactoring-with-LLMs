#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

std::string reverse_string(std::string s) {
    std::reverse(s.begin(), s.end());
    
//    int left = 0;
//    int right = s.length() - 1;
//
//    while (left < right) {
//        if (s[left] != s[right])
//            std::swap(s[left], s[right]);
//
//        ++left;
//        --right;
//    }
    
    return s;
}

}  // namespace reverse_string
