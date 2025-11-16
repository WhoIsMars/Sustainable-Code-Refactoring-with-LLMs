#include "pangram.h"
#include <bitset>
#include <cctype>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    alphabet letters;
    int remaining = pangram::ALPHABET_SIZE;
    for (const char ch : sentence) {
        if (std::isalpha(ch)) {
            auto idx = pangram::letter_idx(ch);
            if (!letters.test(idx)) {
                letters.set(idx);
                if (--remaining == 0) return true;
            }
        }
    }
    return false;
}