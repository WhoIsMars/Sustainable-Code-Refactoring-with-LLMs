#include "pangram.h"
#include <bitset>

using std::string;
using alphabet = std::bitset<pangram::ALPHABET_SIZE>;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    alphabet letters {};
    for (const char ch: sentence) if (isalpha(ch)) {
        letters.set(pangram::letter_idx(ch));
    }
    return letters.all();
}
