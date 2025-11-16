#include "isogram.h"

#include <cctype>

namespace isogram {
    bool is_isogram(const std::string& word) {
        unsigned int letters_seen = 0;

        for (char c : word) {
            if (!std::isalpha(c)) {
                continue;
            }

            c = std::tolower(c);
            unsigned int mask = 1u << (c - 'a');

            if (letters_seen & mask) {
                return false;
            }
            letters_seen |= mask;
        }

        return true;
    }
} // namespace isogram