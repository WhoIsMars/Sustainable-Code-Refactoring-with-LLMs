#include <bitset>
#include <cctype>

#include "isogram.h"

namespace isogram
{
bool is_isogram(const std::string phrase)
{
    std::bitset<26> seen;
    
    for (char ch : phrase)
    {
        if (std::isalpha(ch))
        {
            int index = std::tolower(ch) - 'a';
            if (seen[index])
                return false;
            seen[index] = true;
        }
    }
    return true;
}
} // namespace isogram