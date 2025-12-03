#include <unordered_set>
#include <cctype>
#include <string>

#include "isogram.h"

namespace isogram
{
bool is_isogram(const std::string phrase)
{
    std::unordered_set<char> seen_chars;
    for (char ch : phrase)
    {
        if (std::isalpha(ch))
        {
            char lower_ch = std::tolower(ch);
            if (seen_chars.find(lower_ch) != seen_chars.end())
                return false;
            seen_chars.insert(lower_ch);
        }
    }
    return true;
}
} // namespace isogram