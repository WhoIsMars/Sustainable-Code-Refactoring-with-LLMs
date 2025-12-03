#include "etl.h"
#include <unordered_map>
#include <vector>
#include <cctype>

namespace etl {
    std::unordered_map<char, int> transform(const std::unordered_map<int, std::vector<char>>& old) {
        std::unordered_map<char, int> ans;
        for (const auto& [key, values] : old) {
            for (char ch : values) {
                ans[std::tolower(ch)] = key;
            }
        }
        return ans;
    }
}