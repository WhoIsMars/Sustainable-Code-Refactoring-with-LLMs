#include "isogram.h"

#include <cctype>
#include <cstdint>

namespace isogram {
    bool is_isogram(const std::string& word) {
        std::uint32_t letters_seen = 0;

        for (char c : word) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                const auto position = (c | 32) - 'a';
                const std::uint32_t mask = 1U << position;
                
                if (letters_seen & mask) {
                    return false;
                }
                letters_seen |= mask;
            }
        }

        return true;
    }
} // namespace isogram