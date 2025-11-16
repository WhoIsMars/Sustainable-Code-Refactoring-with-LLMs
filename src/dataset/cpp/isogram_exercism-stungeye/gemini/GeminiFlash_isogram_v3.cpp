#include "isogram.h"

#include <cctype>

namespace isogram {
    inline const int letters_in_alphabet = 26;

    bool is_isogram(const std::string& word) {
        unsigned int letters_seen = 0;

        for (auto c : word) {
            if (!std::isalpha(c)) {
                continue;
            }

            const auto position = std::tolower(c) - 'a';
            const unsigned int bitmask = 1 << position;

            if (letters_seen & bitmask) {
                return false;
            }
            letters_seen |= bitmask;
        }

        return true;
    }
} // namespace isogram