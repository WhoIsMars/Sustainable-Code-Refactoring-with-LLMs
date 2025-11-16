#include "pangram.h"
#include <bitset>
#include <cctype>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    alphabet letters;
    for (const char ch : sentence) {
        if (unsigned char uch = ch; std::isalpha(uch)) {
            letters.set(pangram::letter_idx(uch));
            if (letters.all()) return true;
        }
    }
    return false;
}