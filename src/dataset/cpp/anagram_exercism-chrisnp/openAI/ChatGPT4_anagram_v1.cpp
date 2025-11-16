#include "anagram.h"
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;

anagram::anagram::anagram(const string word) {
    this->subject = word;
    this->normal = word;
    std::transform(this->normal.begin(), this->normal.end(), this->normal.begin(), ::tolower);
    std::sort(this->normal.begin(), this->normal.end());
}

vector<string> anagram::anagram::matches(vector<string> const &candidates) noexcept 
{
    vector<string> matching;
    matching.reserve(candidates.size()); // Reserve space to minimize reallocations
    for (const auto& candidate : candidates) 
    {
        if (candidate.size() != this->subject.size()) continue; // Skip if lengths differ

        string lowerCandidate = candidate;
        std::transform(lowerCandidate.begin(), lowerCandidate.end(), lowerCandidate.begin(), ::tolower);

        if (lowerCandidate == this->subject) continue; // Skip identical words

        string sortedCandidate = lowerCandidate;
        std::sort(sortedCandidate.begin(), sortedCandidate.end());

        if (sortedCandidate == this->normal) {
            matching.push_back(candidate);
        }
    }
    return matching;
}