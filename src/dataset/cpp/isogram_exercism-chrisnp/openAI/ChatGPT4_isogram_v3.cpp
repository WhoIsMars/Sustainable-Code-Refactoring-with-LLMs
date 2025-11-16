#include "isogram.h"
#include <bitset>

bool isogram::is_isogram(const std::string& word) {
    if (word.size() <= 1) return true;
    std::bitset<26> charFlag;
    for (char checkChar : word) {
        if (!isalpha(checkChar)) continue;
        size_t checkIndex = tolower(checkChar) - 'a';
        if (charFlag.test(checkIndex)) return false;
        charFlag.set(checkIndex);
    }
    return true;
}