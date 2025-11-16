#include "anagram.h"
#include <algorithm>

using std::string;
using std::vector;

anagram::anagram::anagram(const string& word) {
    subject.reserve(word.size());
    subject = word;
    std::transform(subject.begin(), subject.end(), subject.begin(), ::tolower);
    normal = subject;
    std::sort(normal.begin(), normal.end());
}

vector<string> anagram::anagram::matches(vector<string> const &candidates) noexcept 
{
    vector<string> matching;
    matching.reserve(candidates.size());
    
    for (const auto& candidate : candidates) 
    {
        if (candidate.size() != subject.size()) continue;
        
        string word;
        word.reserve(candidate.size());
        word = candidate;
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if (word == subject) continue;
        
        std::sort(word.begin(), word.end());
        if (word == normal)
            matching.push_back(candidate);
    }
    return matching;
}