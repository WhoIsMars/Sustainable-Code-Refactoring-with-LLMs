#include "isogram.h"

#include <bitset>
#include <cctype>

namespace isogram {

    bool is_isogram(const std::string str) {
        std::bitset<26> seen;
        
        for (char c : str) {
            if (std::isalpha(c)) {
                int index = std::tolower(c) - 'a';
                if (seen[index]) return false;
                seen[index] = true;
            }
        }
        
        return true;
    }

}  // namespace isogram