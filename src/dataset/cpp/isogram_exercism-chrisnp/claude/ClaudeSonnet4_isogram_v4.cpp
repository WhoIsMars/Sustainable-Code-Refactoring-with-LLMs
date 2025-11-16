#include "isogram.h"

bool isogram::is_isogram(const std::string word) {
    if (word.length() <= 1) return true;
    
    std::uint32_t charFlag = 0;
    
    for (char c : word) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            const std::uint32_t bit = 1U << ((c | 32) - 'a');
            if (charFlag & bit) return false;
            charFlag |= bit;
        }
    }
    return true;
}