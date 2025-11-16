#include <unordered_set>
#include <cctype>
#include "isogram.h"

bool isogram::is_isogram(std::string const& text_to_test)
{
    std::unordered_set<char> seen_chars;
    for (char c : text_to_test) {
        if (std::isalpha(c)) {
            char lower_c = static_cast<char>(std::tolower(c));
            if (!seen_chars.insert(lower_c).second) {
                return false;
            }
        }
    }
    return true;
}