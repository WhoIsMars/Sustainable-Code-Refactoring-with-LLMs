#include <bitset>
#include <cctype>
#include "pangram.h"

namespace pangram {
    static constexpr int ascii_lowercase_start = 97;

    bool is_pangram(const std::string& text) {
        std::bitset<26> alphabet_flags;

        for (char ch : text) {
            if (std::isalpha(ch)) {
                alphabet_flags.set(std::tolower(ch) - ascii_lowercase_start);
                if (alphabet_flags.all()) {
                    return true;
                }
            }
        }

        return false;
    }
}  // namespace pangram