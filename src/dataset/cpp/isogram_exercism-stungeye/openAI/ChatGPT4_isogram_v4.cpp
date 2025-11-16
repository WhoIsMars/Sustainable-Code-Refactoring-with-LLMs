#include "isogram.h"

#include <bitset>
#include <cctype>
#include <algorithm>

namespace isogram {
    constexpr int letters_in_alphabet = 26;

    bool is_isogram(const std::string& word) {
        std::bitset<letters_in_alphabet> letters_seen;

        for (char c : word) {
            if (!std::isalpha(c)) continue;

            c = std::tolower(c);
            const auto position = c - 'a';

            if (letters_seen.test(position)) return false;
            letters_seen.set(position);
        }

        return true;
    }
} // namespace isogram