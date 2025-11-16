#include "anagram.h"
#include <algorithm>

using std::string;
using std::vector;

anagram::anagram::anagram(const string word) {
    this->subject = word;
    std::transform(this->subject.begin(), this->subject.end(),
                   this->subject.begin(), ::tolower);
    this->normal = this->subject;
    std::sort(this->normal.begin(), this->normal.end());
}

vector<string> anagram::anagram::matches(vector<string> const &candidates) noexcept 
{
    vector<string> matching;
    matching.reserve(candidates.size());
    
    for (const auto& candidate : candidates) 
    {
        if (candidate.length() != subject.length()) continue;
        
        string word = candidate;
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if (word == subject) continue;
        
        std::sort(word.begin(), word.end());
        
        if (word == normal) {
            matching.push_back(candidate);
        }
    }
    return matching;
}