#include "isogram.h"

#include <unordered_set>
#include <cctype>

namespace isogram {

    bool is_isogram(const std::string& str) {
        std::unordered_set<char> seenChars;

        for (char c : str) {
            if (std::isalpha(c)) {
                char lowerC = std::tolower(c);
                if (!seenChars.insert(lowerC).second) {
                    return false;
                }
            }
        }

        return true;
    }

}  // namespace isogram