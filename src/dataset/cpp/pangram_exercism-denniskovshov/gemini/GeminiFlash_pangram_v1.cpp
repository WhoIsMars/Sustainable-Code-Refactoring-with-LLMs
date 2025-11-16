#include "pangram.h"
#include <cctype>

namespace pangram {
    bool is_pangram(const std::string& text) {
        if (text.length() < 26) return false;

        std::bitset<26> letters;

        for (unsigned char ch : text) {
            if (std::isalpha(ch)) {
                letters.set(std::tolower(ch) - 'a');
            }
        }

        return letters.all();
    }
}  // namespace pangram