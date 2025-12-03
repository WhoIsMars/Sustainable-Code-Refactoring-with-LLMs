#include "isogram.h"
#include <string>
#include <cctype>
#include <unordered_set>

namespace isogram {

bool is_isogram(const std::string& word) {
    std::unordered_set<char> seen;
    for (char c : word) {
        if (std::isalpha(c)) {
            char lower_c = std::tolower(c);
            if (seen.count(lower_c) > 0) {
                return false;
            }
            seen.insert(lower_c);
        }
    }
    return true;
}

}