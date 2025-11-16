#include "anagram.h"
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <cctype>

namespace anagram {

    anagram::anagram(std::string word) : word(std::move(word)) {}

    std::vector<std::string> anagram::matches(std::list<std::string> words) {
        std::string normalized_word = word;
        std::transform(normalized_word.begin(), normalized_word.end(), normalized_word.begin(), 
                      [](unsigned char c) { return std::tolower(c); });
        
        std::string key = normalized_word;
        std::sort(key.begin(), key.end());
        
        std::vector<std::string> ans;
        ans.reserve(words.size());
        
        for (const auto& candidate : words) {
            if (candidate.length() != word.length()) continue;
            
            std::string normalized_candidate = candidate;
            std::transform(normalized_candidate.begin(), normalized_candidate.end(), 
                          normalized_candidate.begin(), [](unsigned char c) { return std::tolower(c); });
            
            if (normalized_word == normalized_candidate) continue;
            
            std::sort(normalized_candidate.begin(), normalized_candidate.end());
            
            if (key == normalized_candidate) {
                ans.push_back(candidate);
            }
        }
        
        return ans;
    }
}