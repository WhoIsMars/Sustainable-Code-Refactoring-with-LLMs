#include "anagram.h"
#include <bits/stdc++.h>
using namespace std;

namespace anagram{

        anagram::anagram(string word) : word(std::move(word))
        {
        }
        
        vector<string> anagram::matches(list<string> words)
        {
            string key = word;
            transform(key.begin(), key.end(), key.begin(), ::tolower);
            sort(key.begin(), key.end());
            
            string word_lower = word;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);
            
            vector<string> ans;
            ans.reserve(words.size());
            
            for(const auto& candidate : words)
            {
                string candidate_lower = candidate;
                transform(candidate_lower.begin(), candidate_lower.end(), candidate_lower.begin(), ::tolower);
                
                if(word_lower == candidate_lower) continue;
                
                sort(candidate_lower.begin(), candidate_lower.end());
                if(key == candidate_lower)
                {
                    ans.push_back(candidate);
                }
            }
            return ans;
        }

}