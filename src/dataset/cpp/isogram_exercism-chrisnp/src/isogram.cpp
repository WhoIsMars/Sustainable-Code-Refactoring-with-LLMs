#include "isogram.h"

bool isogram::is_isogram(const std::string word) {
    if (word.length() <= 1) return true;
    __uint32_t charFlag { 0 };
    auto alpha { 97 };
    for (auto checkChar : word) {
        if (!(isalpha(checkChar))) continue;
        auto checkIndex { tolower(checkChar) - alpha };
        if (charFlag & 1 << checkIndex) { return false; } 
        else { charFlag |= (1 << checkIndex); }
    }
    return true;
}
