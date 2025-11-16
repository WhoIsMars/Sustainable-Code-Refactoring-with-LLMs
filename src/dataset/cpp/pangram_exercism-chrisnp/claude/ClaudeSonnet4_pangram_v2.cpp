#include "pangram.h"
#include <cstdint>

using std::string;

bool pangram::is_pangram(const string &sentence) noexcept {
    if (sentence.size() < pangram::ALPHABET_SIZE) return false;
    
    uint32_t letters = 0;
    constexpr uint32_t all_letters = (1U << pangram::ALPHABET_SIZE) - 1;
    
    for (const char ch : sentence) {
        if ((ch | 0x20) >= 'a' && (ch | 0x20) <= 'z') {
            letters |= 1U << ((ch | 0x20) - 'a');
            if (letters == all_letters) return true;
        }
    }
    
    return letters == all_letters;
}