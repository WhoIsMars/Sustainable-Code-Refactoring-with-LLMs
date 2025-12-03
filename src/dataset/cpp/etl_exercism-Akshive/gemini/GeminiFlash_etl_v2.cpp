#include "etl.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>

namespace etl {
    std::map<char, int> transform(const std::map<int, std::vector<char>>& old) {
        std::map<char, int> ans;
        for (const auto& [key, values] : old) {
            for (char value : values) {
                ans[std::tolower(value)] = key;
            }
        }
        return ans;
    }
}