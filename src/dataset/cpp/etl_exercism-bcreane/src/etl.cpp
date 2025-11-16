#include "etl.h"
#include <cctype>

std::map<char, int>
etl::transform(const std::map<int, std::vector<char> >& old)
{
    std::map<char, int> updated;

    for (auto it = old.begin(); it != old.end(); ++it) {
        int points = it->first;
        const std::vector<char>& list = it->second;
        for (char l : list) {
            updated[std::tolower(l)] = points;
        }
    }
    
    return updated;
}
