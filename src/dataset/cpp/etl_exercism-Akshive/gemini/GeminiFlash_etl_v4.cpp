#include "etl.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>

namespace etl {
    std::map<char, int> transform(std::map<int, std::vector<char>> old) {
        std::map<char, int> ans;
        ans.reserve(old.size());

        for (const auto& [key, values] : old) {
            for (const char& value : values) {
                ans[std::tolower(value)] = key;
            }
        }
        return ans;
    }
}