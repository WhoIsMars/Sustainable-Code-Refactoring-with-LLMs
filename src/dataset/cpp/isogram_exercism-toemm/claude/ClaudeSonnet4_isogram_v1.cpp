#include "isogram.h"

#include <string>
#include <bitset>

namespace isogram {

bool is_isogram(const std::string& str) {
    std::bitset<26> seen;
    
    for (char ch : str) {
        if (isalpha(ch)) {
            int index = tolower(ch) - 'a';
            if (seen[index]) return false;
            seen[index] = true;
        }
    }
    
    return true;
}

}  // namespace isogram