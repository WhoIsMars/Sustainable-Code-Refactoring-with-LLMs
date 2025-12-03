#include "isogram.h"
#include <string>
#include <bitset>
#include <cctype>

namespace isogram {

    bool is_isogram(std::string word) {
        std::bitset<26> seen;
        
        for (char c : word) {
            if (std::isalpha(c)) {
                int index = std::tolower(c) - 'a';
                if (seen[index]) {
                    return false;
                }
                seen[index] = true;
            }
        }
        return true;
    }

}