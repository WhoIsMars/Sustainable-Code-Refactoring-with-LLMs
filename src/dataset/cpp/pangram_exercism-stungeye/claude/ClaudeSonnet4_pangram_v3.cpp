#include "pangram.h"

#include <bitset>

namespace pangram {
    inline const int letters_in_alphabet = 26;

    bool is_pangram(std::string_view sentence) {
        std::bitset<letters_in_alphabet> letters_seen;

        for (auto c : sentence) {
            if ((c >= 'A') && (c <= 'Z')) {
                letters_seen.set(c - 'A');
            } else if ((c >= 'a') && (c <= 'z')) {
                letters_seen.set(c - 'a');
            }
            
            if (letters_seen.all()) {
                return true;
            }
        }

        return letters_seen.all();
    }
} // namespace pangram