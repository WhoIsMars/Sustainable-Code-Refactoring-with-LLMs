#include "anagram.h"
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;

anagram::anagram::anagram(const string& word) {
    subject = word;
    std::transform(subject.begin(), subject.end(), subject.begin(), ::tolower);
    normal = subject;
    std::sort(normal.begin(), normal.end());
}

vector<string> anagram::anagram::matches(const vector<string>& candidates) const noexcept {
    vector<string> matching;
    matching.reserve(candidates.size()); // Reserve space to reduce reallocations

    for (const auto& candidate : candidates) {
        if (candidate.size() != subject.size()) continue; // Skip if lengths differ

        string lowerCandidate = candidate;
        std::transform(lowerCandidate.begin(), lowerCandidate.end(), lowerCandidate.begin(), ::tolower);

        if (lowerCandidate == subject) continue; // Skip identical words

        string sortedCandidate = lowerCandidate;
        std::sort(sortedCandidate.begin(), sortedCandidate.end());

        if (sortedCandidate == normal) {
            matching.push_back(candidate);
        }
    }

    matching.shrink_to_fit(); // Reduce memory usage
    return matching;
}