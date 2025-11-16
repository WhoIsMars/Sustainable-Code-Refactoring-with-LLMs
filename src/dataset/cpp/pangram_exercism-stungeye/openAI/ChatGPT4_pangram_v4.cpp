#include "pangram.h"

#include <bitset>
#include <cctype>

namespace pangram {
    inline constexpr int letters_in_alphabet = 26;

    bool is_pangram(std::string_view sentence) {
        std::bitset<letters_in_alphabet> letters_seen;

        for (char c : sentence) {
            if (std::isalpha(c)) {
                letters_seen.set(std::tolower(c) - 'a');
                if (letters_seen.all()) return true;
            }
        }

        return false;
    }
} // namespace pangram