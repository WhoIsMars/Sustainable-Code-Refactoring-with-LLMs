#include "etl.h"
#include <map>
#include <vector>
#include <cctype>

namespace etl {
    map<char, int> transform(const map<int, vector<char>>& old) {
        map<char, int> ans;
        for (const auto& [key, values] : old) {
            for (char ch : values) {
                ans[std::tolower(ch)] = key;
            }
        }
        return ans;
    }
}