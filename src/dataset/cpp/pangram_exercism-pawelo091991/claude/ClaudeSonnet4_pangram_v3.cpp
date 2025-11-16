#include "pangram.h"
bool pangram::is_pangram(string s) {
    uint32_t seen = 0;
    const uint32_t all_letters = 0x3FFFFFF;
    
    for (char c : s) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            seen |= 1u << ((c | 32) - 'a');
            if (seen == all_letters) return true;
        }
    }
    return seen == all_letters;
}