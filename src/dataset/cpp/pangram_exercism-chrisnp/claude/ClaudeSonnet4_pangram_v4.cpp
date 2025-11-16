#include "pangram.h"
#include <bitset>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    
    alphabet letters {};
    const char* ptr = sentence.data();
    const char* end = ptr + sentence.size();
    
    while (ptr < end) {
        const char ch = *ptr++;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            letters.set(pangram::letter_idx(ch));
            if (letters.all()) return true;
        }
    }
    
    return false;
}