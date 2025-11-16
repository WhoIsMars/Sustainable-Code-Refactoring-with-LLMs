#include <bitset>
#include "pangram.h"

namespace pangram {
    static constexpr int ascii_lowercase_start = 97;
    static constexpr int ascii_uppercase_start = 65;

    bool is_pangram(const std::string& text) {
        std::bitset<26> letter_flags;

        for (char ch : text) {
            if (ch >= 'a' && ch <= 'z') {
                letter_flags.set(ch - ascii_lowercase_start);
            }
            else if (ch >= 'A' && ch <= 'Z') {
                letter_flags.set(ch - ascii_uppercase_start);
            }
            
            if (letter_flags.all()) {
                return true;
            }
        }
        
        return letter_flags.all();
    }
}