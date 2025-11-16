#include "isogram.h"

#include <cctype>
#include <string_view>

namespace isogram {
    bool is_isogram(std::string_view word) {
        unsigned int letters_seen = 0;

        for (char c : word) {
            if (!std::isalpha(c)) {
                continue;
            }

            const int position = std::tolower(c) - 'a';
            const unsigned int mask = 1 << position;

            if (letters_seen & mask) {
                return false;
            }

            letters_seen |= mask;
        }

        return true;
    }
} // namespace isogram