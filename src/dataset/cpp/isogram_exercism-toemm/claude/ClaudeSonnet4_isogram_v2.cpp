#include "isogram.h"

#include <string>

namespace isogram {

bool is_isogram(const std::string& str) {
    bool seen[26] = {false};
    
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