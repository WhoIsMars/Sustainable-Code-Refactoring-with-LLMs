#include "isogram.h"

#include <string>
#include <bitset>
#include <cctype>

namespace isogram {

bool is_isogram(const std::string& str) {
    std::bitset<26> seen;
    
    for (char ch : str) {
        if (std::isalpha(ch)) {
            int index = std::tolower(ch) - 'a';
            if (seen[index]) return false;
            seen[index] = true;
        }
    }
    
    return true;
}

}  // namespace isogram