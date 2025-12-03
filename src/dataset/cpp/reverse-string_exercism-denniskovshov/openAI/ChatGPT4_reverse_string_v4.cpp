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
        for (size_t i = 0; i < len / 2; ++i) {
            std::swap(str[i], str[len - i - 1]);
        }
        return str;
    }
}