#include "pangram.h"

#include <algorithm>
#include <cctype>
#include <bitset>

namespace pangram {
    inline const int letters_in_alphabet = 26;

    bool is_pangram(std::string_view sentence) {
        std::bitset<letters_in_alphabet> letters_seen;
        for (unsigned char c : sentence) {
            if (std::isalpha(c)) {
                letters_seen.set(std::tolower(c) - 'a');
            }
        }
        return letters_seen.all();
    }
} // namespace pangram