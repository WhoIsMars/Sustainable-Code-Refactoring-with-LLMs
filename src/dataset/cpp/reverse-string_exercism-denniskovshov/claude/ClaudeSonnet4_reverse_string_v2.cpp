#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {
    std::string reverse_string(std::string str) {
        std::reverse(str.begin(), str.end());
        return str;
    }

    std::string reverse_string_iter(const std::string& str) {
        return std::string(str.crbegin(), str.crend());
    }

    std::string reverse_string_manual(std::string str) {
        const size_t len = str.length();
        if (len <= 1) return str;
        
        const size_t half = len >> 1;
        for (size_t i = 0; i < half; ++i) {
            std::swap(str[i], str[len - 1 - i]);
        }
        
        return str;
    }
}