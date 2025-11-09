#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

    std::string reverse_string(std::string str) {
        std::reverse(str.begin(), str.end());
        return str;
    }

    std::string reverse_string_iter(const std::string& str) {
        return {str.rbegin(), str.rend()};
    }

    std::string reverse_string_manual(std::string str) {
        size_t len = str.length();
        if (len <= 1)
            return str;

        for (size_t start = 0, end = len - 1; start < end; ++start, --end) {
            std::swap(str[start], str[end]);
        }
        
        return str;
    }
}