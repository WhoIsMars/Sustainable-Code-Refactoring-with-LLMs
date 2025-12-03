#include <bitset>
#include <cctype>
#include "pangram.h"

namespace pangram {
    static constexpr int ascii_lowercase_start = 97;

    bool is_pangram(const std::string& text) {
        std::bitset<26> flags;

        for (char ch : text) {
            if (std::isalpha(ch)) {
                flags.set(std::tolower(ch) - ascii_lowercase_start);
                if (flags.all()) return true;
            }
        }

        return false;
    }
}  // namespace pangram