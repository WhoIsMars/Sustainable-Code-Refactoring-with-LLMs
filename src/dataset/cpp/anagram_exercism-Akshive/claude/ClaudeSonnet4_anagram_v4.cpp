#include "anagram.h"
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <cctype>

namespace anagram {

    anagram::anagram(std::string word) : word(std::move(word)) {
        std::transform(this->word.begin(), this->word.end(), this->word.begin(), ::tolower);
        std::sort(this->word.begin(), this->word.end());
    }

    std::vector<std::string> anagram::matches(std::list<std::string> words) {
        std::vector<std::string> ans;
        ans.reserve(words.size());
        
        for (const auto& candidate : words) {
            if (candidate.length() != word.length()) continue;
            
            std::string lower_candidate;
            lower_candidate.reserve(candidate.length());
            std::transform(candidate.begin(), candidate.end(), std::back_inserter(lower_candidate), ::tolower);
            
            if (word == lower_candidate) continue;
            
            std::sort(lower_candidate.begin(), lower_candidate.end());
            
            if (word == lower_candidate) {
                ans.push_back(candidate);
            }
        }
        
        return ans;
    }
}