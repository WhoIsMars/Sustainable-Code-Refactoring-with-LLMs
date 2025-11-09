#include "reverse_string.h"
#include <algorithm>
#include <string>

namespace reverse_string {

    std::string reverse_string(std::string str) {
        std::reverse(str.begin(), str.end());
        return str;
    }

    std::string reverse_string_iter(const std::string& str) {
        return std::string(str.rbegin(), str.rend());
    }

    std::string reverse_string_manual(std::string str) {
        size_t len = str.length();
        if (len <= 1) return str;

        for (size_t i = 0; i < len / 2; ++i) {
            std::swap(str[i], str[len - 1 - i]);
        }
        return str;
    }
}