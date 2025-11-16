#include "isogram.h"

bool isogram::is_isogram(const std::string& word) {
    if (word.length() <= 1) return true;
    
    std::uint32_t charFlag = 0;
    
    for (char c : word) {
        if (!std::isalpha(static_cast<unsigned char>(c))) continue;
        
        int index = std::tolower(static_cast<unsigned char>(c)) - 'a';
        std::uint32_t mask = 1U << index;
        
        if (charFlag & mask) return false;
        charFlag |= mask;
    }
    return true;
}