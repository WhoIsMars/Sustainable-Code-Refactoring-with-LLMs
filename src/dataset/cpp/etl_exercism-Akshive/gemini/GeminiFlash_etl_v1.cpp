#include "etl.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>

namespace etl {
    std::map<char, int> transform(std::map<int, std::vector<char>> const& old) {
        std::map<char, int> ans;
        ans.reserve(old.size()); // Pre-allocate memory to potentially reduce reallocations

        for (auto const& [key, values] : old) {
            for (char const& value : values) {
                ans[std::tolower(value)] = key;
            }
        }
        return ans;
    }
}