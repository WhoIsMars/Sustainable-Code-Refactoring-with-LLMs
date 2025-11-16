#include "anagram.h"
#include <algorithm>
#include <cctype>

using std::string;
using std::vector;

anagram::anagram::anagram(const string word) : subject(word) {
    std::transform(subject.begin(), subject.end(), subject.begin(), 
                   [](unsigned char c) { return std::tolower(c); });
    normal = subject;
    std::sort(normal.begin(), normal.end());
}

vector<string> anagram::anagram::matches(const vector<string>& candidates) noexcept 
{
    vector<string> matching;
    matching.reserve(candidates.size());
    
    for (const auto& candidate : candidates) {
        if (candidate.length() != subject.length()) {
            continue;
        }
        
        string word;
        word.reserve(candidate.length());
        std::transform(candidate.begin(), candidate.end(), std::back_inserter(word),
                       [](unsigned char c) { return std::tolower(c); });
        
        if (word == subject) {
            continue;
        }
        
        std::sort(word.begin(), word.end());
        if (word == normal) {
            matching.push_back(candidate);
        }
    }
    
    return matching;
}