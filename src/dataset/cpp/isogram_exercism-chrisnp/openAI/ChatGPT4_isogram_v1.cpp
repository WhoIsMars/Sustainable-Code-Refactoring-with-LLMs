#include "isogram.h"

bool isogram::is_isogram(const std::string& word) {
    if (word.empty()) return true;
    __uint32_t charFlag = 0;
    for (char checkChar : word) {
        if (!isalpha(checkChar)) continue;
        int checkIndex = tolower(checkChar) - 'a';
        __uint32_t mask = 1u << checkIndex;
        if (charFlag & mask) return false;
        charFlag |= mask;
    }
    return true;
}