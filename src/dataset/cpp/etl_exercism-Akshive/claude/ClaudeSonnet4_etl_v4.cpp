#include "etl.h"
#include <map>
#include <vector>
#include <cctype>

namespace etl{
    std::map<char, int> transform(const std::map<int, std::vector<char>>& old)
    {
        std::map<char, int> ans;
        ans.reserve(old.size() * 10);
        
        for(const auto& pair : old)
        {
            const int key = pair.first;
            const auto& values = pair.second;

            for(char c : values)
            {
                ans[std::tolower(c)] = key;
            }
        }
        return ans;
    }
}