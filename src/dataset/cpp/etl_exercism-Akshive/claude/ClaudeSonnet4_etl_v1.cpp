#include "etl.h"
#include <map>
#include <vector>
#include <cctype>
using namespace std;

namespace etl{
    map<char, int> transform(map<int, vector<char>> old)
    {
        map<char, int> ans;
        ans.reserve(old.size() * 10); // Reserve space to reduce reallocations
        
        for(const auto& pair : old)
        {
            const int key = pair.first;
            const auto& values = pair.second;

            for(char c : values)
            {
                ans[tolower(c)] = key;
            }
        }
        return ans;
    }
}