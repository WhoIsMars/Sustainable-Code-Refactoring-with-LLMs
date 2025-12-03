#include "etl.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>

namespace etl {
    std::map<char, int> transform(const std::map<int, std::vector<char>>& old) {
        std::map<char, int> ans;
        ans.reserve(old.size() * 2); // Pre-allocate space to potentially reduce reallocations

        for (const auto& pair : old) {
            int key = pair.first;
            const auto& values = pair.second;

            for (char value : values) {
                ans[std::tolower(value)] = key;
            }
        }
        return ans;
    }
}