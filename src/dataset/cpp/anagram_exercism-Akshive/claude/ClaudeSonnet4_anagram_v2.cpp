#include "anagram.h"
#include <bits/stdc++.h>
using namespace std;

namespace anagram{

        anagram::anagram(string word) : word(std::move(word))
        {
            transform(this->word.begin(), this->word.end(), this->word.begin(), ::tolower);
            key = this->word;
            sort(key.begin(), key.end());
        }
        
        vector<string> anagram::matches(list<string> words)
        {
            vector<string> ans;
            ans.reserve(words.size());
            
            for(const auto& candidate : words)
            {
                if(word.size() != candidate.size()) continue;
                
                string candidate_lower = candidate;
                transform(candidate_lower.begin(), candidate_lower.end(), candidate_lower.begin(), ::tolower);
                
                if(word == candidate_lower) continue;
                
                sort(candidate_lower.begin(), candidate_lower.end());
                if(key == candidate_lower)
                {
                    ans.push_back(candidate);
                }
            }
            return ans;
        }

private:
        string key;
}