#include "anagram.h"
#include <bits/stdc++.h>
using namespace std;

namespace anagram{

        anagram::anagram(string word)
        {
            this->word = word;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            this->sorted_word = word;
            sort(this->sorted_word.begin(), this->sorted_word.end());
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
                if(sorted_word == candidate_lower)
                {
                    ans.push_back(candidate);
                }
            }
            return ans;
        }

private:
        string sorted_word;
}