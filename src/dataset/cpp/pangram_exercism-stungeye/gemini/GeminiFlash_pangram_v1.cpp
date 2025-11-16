#include "pangram.h"

#include <algorithm>
#include <cctype>

namespace pangram {
    inline const int letters_in_alphabet = 26;

    bool is_pangram(std::string_view sentence) {
        if (sentence.length() < letters_in_alphabet) {
            return false;
        }

        std::array<bool, letters_in_alphabet> letters_seen{};

        for (unsigned char c : sentence) {
            if (std::isalpha(c)) {
                size_t index = std::tolower(c) - 'a';
                if (index < letters_in_alphabet) {
                    letters_seen[index] = true;
                }
            }
        }

        return std::all_of(letters_seen.begin(), letters_seen.end(), [](bool b){ return b; });
    }
} // namespace pangram