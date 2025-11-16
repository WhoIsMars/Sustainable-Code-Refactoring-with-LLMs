#include "isogram.h"

#include <string>
#include <unordered_set>
#include <cctype>

namespace isogram {

bool is_isogram(const std::string& str) {
    std::unordered_set<char> seen_chars;

    for (char ch : str) {
        if (std::isalpha(ch)) {
            ch = std::tolower(ch);
            if (!seen_chars.insert(ch).second) {
                return false;
            }
        }
    }

    return true;
}

}  // namespace isogram