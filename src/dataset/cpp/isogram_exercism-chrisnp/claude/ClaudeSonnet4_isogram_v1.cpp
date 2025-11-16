#include "isogram.h"

bool isogram::is_isogram(const std::string word) {
    if (word.length() <= 1) return true;
    
    __uint32_t charFlag = 0;
    
    for (char c : word) {
        if ((c | 32) < 'a' || (c | 32) > 'z') continue;
        
        const int bit = (c | 32) - 'a';
        const __uint32_t mask = 1U << bit;
        
        if (charFlag & mask) return false;
        charFlag |= mask;
    }
    return true;
}