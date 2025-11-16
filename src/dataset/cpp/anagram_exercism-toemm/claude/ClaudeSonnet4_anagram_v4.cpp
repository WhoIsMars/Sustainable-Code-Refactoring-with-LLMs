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
}

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> result;
    const auto str_size = str.size();
    
    string sorted_str = str;
    std::sort(sorted_str.begin(), sorted_str.end());
    
    result.reserve(candidates.size());
    
    for (const auto& candidate : candidates) {
        if (candidate.size() != str_size) continue;
        
        string candidate_lower = candidate;
        tolower(candidate_lower);
        
        if (candidate_lower == str) continue;
        
        std::sort(candidate_lower.begin(), candidate_lower.end());
        
        if (candidate_lower == sorted_str) {
            result.insert(candidate);
        }
    }
    
    return result;
}

}  // namespace anagram