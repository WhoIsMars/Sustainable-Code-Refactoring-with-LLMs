#include "isogram.h"

#include <cctype>
#include <string>

namespace isogram {
    bool is_isogram(const std::string& word) {
        if (word.empty()) return true;

        unsigned int seen_letters = 0;

        for (char c : word) {
            if (!std::isalpha(c)) continue;

            char lower_c = std::tolower(c);
            int position = lower_c - 'a';

            if ((seen_letters & (1 << position)) != 0) {
                return false;
            }

            seen_letters |= (1 << position);
        }

        return true;
    }
} // namespace isogram