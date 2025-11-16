#include "pangram.h"
#include <bitset>
#include <cctype>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    alphabet letters;
    for (const char ch : sentence) {
        if (std::isalpha(ch)) {
            letters.set(pangram::letter_idx(ch));
            if (letters.all()) return true; // Early exit when all letters are found
        }
    }
    return false;
}