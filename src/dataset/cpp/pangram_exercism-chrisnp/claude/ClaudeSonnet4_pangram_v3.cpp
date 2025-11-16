#include "pangram.h"
#include <bitset>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    
    alphabet letters {};
    std::size_t unique_count = 0;
    
    for (const char ch : sentence) {
        if (isalpha(ch)) {
            const std::size_t idx = pangram::letter_idx(ch);
            if (!letters.test(idx)) {
                letters.set(idx);
                if (++unique_count == pangram::ALPHABET_SIZE) {
                    return true;
                }
            }
        }
    }
    
    return false;
}