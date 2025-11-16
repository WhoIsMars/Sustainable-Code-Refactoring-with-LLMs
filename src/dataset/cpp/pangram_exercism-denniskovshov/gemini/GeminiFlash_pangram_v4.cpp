#include <string>
#include <cctype>
#include <bitset>

#include "pangram.h"

namespace pangram {

bool is_pangram(const std::string& text) {
    std::bitset<26> letters;
    size_t count = 0;

    for (unsigned char ch : text) {
        if (std::isalpha(ch)) {
            unsigned char lower_ch = std::tolower(ch);
            size_t index = lower_ch - 'a';
            if (!letters[index]) {
                letters[index] = true;
                count++;
                if (count == 26) return true;
            }
        }
    }

    return count == 26;
}

}  // namespace pangram