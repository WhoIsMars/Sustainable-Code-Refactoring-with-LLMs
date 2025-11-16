#include "anagram.h"
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;

anagram::anagram::anagram(const string word) {
    this->subject = word;
    this->normal = word;
    std::transform(this->subject.begin(), this->subject.end(), this->subject.begin(), ::tolower);
    std::transform(this->normal.begin(), this->normal.end(), this->normal.begin(), ::tolower);
    std::sort(this->normal.begin(), this->normal.end());
}

vector<string> anagram::anagram::matches(vector<string> const &candidates) noexcept {
    vector<string> matching;
    matching.reserve(candidates.size());
    for (const auto& candidate : candidates) {
        if (candidate.size() != this->subject.size()) continue;

        string lowerCandidate = candidate;
        std::transform(lowerCandidate.begin(), lowerCandidate.end(), lowerCandidate.begin(), ::tolower);

        if (lowerCandidate == this->subject) continue;

        string sortedCandidate = lowerCandidate;
        std::sort(sortedCandidate.begin(), sortedCandidate.end());

        if (sortedCandidate == this->normal) {
            matching.push_back(candidate);
        }
    }
    return matching;
}