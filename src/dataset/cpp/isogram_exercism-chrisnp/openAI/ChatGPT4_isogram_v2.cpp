#include "isogram.h"
#include <bitset>

bool isogram::is_isogram(const std::string& word) {
    if (word.empty()) return true;
    std::bitset<26> charFlag;
    for (char checkChar : word) {
        if (isalpha(checkChar)) {
            int checkIndex = tolower(checkChar) - 'a';
            if (charFlag.test(checkIndex)) return false;
            charFlag.set(checkIndex);
        }
    }
    return true;
}