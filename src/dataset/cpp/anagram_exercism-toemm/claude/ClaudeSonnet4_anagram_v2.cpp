#include "anagram.h"

#include <algorithm>
#include <cctype>

namespace anagram {

void anagram::tolower(string& str) {
    std::transform(str.begin(), str.end(), str.begin(), 
        [](unsigned char ch) { return std::tolower(ch); });
}

anagram::anagram(string str) : str(std::move(str)) { 
    tolower(this->str); 
    std::sort(this->str.begin(), this->str.end());
}

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> list;
    auto str_size = str.size();

    for (const auto& candidate : candidates) {
        if (candidate.size() != str_size) continue;
        
        auto candidate_lower = candidate;
        tolower(candidate_lower);
        
        if (candidate_lower == str) continue;
        
        std::sort(candidate_lower.begin(), candidate_lower.end());
        
        if (candidate_lower == str) {
            list.insert(candidate);
        }
    }

    return list;
}

}  // namespace anagram