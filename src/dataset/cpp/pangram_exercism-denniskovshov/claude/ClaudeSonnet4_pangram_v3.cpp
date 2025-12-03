#include <bitset>
#include "pangram.h"

namespace pangram {
    bool is_pangram(const std::string& text) {
        std::bitset<26> letter_flags;
        
        for (char ch : text) {
            if (ch >= 'a' && ch <= 'z') {
                letter_flags.set(ch - 'a');
            } else if (ch >= 'A' && ch <= 'Z') {
                letter_flags.set(ch - 'A');
            }
            
            if (letter_flags.all()) {
                return true;
            }
        }
        
        return letter_flags.all();
    }
}