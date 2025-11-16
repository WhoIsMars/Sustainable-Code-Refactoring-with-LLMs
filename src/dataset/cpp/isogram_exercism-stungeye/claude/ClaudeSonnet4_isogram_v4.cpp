#include "isogram.h"

#include <cctype>
#include <cstdint>

namespace isogram {
    bool is_isogram(const std::string& word) {
        std::uint32_t letters_seen = 0;

        for (const char c : word) {
            if (!std::isalpha(static_cast<unsigned char>(c))) {
                continue;
            }

            const auto position = std::tolower(static_cast<unsigned char>(c)) - 'a';
            const std::uint32_t mask = 1U << position;

            if (letters_seen & mask) {
                return false;
            }
            letters_seen |= mask;
        }

        return true;
    }
} // namespace isogram