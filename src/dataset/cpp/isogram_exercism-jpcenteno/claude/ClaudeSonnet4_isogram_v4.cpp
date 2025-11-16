#include "isogram.h"

#include <bitset>
#include <cctype>

namespace isogram {

    bool is_isogram(const std::string str) {
        std::bitset<26> seen;
        
        for (char c : str) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                int index = std::tolower(static_cast<unsigned char>(c)) - 'a';
                if (seen[index]) return false;
                seen[index] = true;
            }
        }
        
        return true;
    }

}  // namespace isogram