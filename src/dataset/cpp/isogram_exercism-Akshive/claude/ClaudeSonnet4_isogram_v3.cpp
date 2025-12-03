#include "isogram.h"
#include <string>
#include <bitset>

namespace isogram {

    bool is_isogram(std::string word) {
        std::bitset<26> seen;
        
        for (char c : word) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            } else if (c < 'a' || c > 'z') {
                continue;
            }
            
            int index = c - 'a';
            if (seen[index]) {
                return false;
            }
            seen[index] = 1;
        }
        
        return true;
    }

}