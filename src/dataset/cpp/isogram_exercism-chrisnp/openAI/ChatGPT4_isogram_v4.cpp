#include "isogram.h"
#include <cctype>

bool isogram::is_isogram(const std::string& word) {
    if (word.empty()) return true;
    uint32_t charFlag = 0;
    for (char checkChar : word) {
        if (!std::isalpha(checkChar)) continue;
        int checkIndex = std::tolower(checkChar) - 'a';
        uint32_t mask = 1u << checkIndex;
        if (charFlag & mask) return false;
        charFlag |= mask;
    }
    return true;
}