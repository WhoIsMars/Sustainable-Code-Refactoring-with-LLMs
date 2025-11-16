#include "anagram.h"
#include <algorithm>
#include <unordered_map>

using std::string;
using std::vector;

anagram::anagram::anagram(const string& word) {
    subject = word;
    normal = subject;
    std::transform(normal.begin(), normal.end(), normal.begin(), ::tolower);
    std::sort(normal.begin(), normal.end());
}

vector<string> anagram::anagram::matches(const vector<string>& candidates) noexcept {
    vector<string> matching;
    matching.reserve(candidates.size());
    for (const auto& candidate : candidates) {
        if (candidate.size() != subject.size()) continue;

        string lowerCandidate = candidate;
        std::transform(lowerCandidate.begin(), lowerCandidate.end(), lowerCandidate.begin(), ::tolower);

        if (lowerCandidate == subject) continue;

        string sortedCandidate = lowerCandidate;
        std::sort(sortedCandidate.begin(), sortedCandidate.end());

        if (sortedCandidate == normal) {
            matching.push_back(candidate);
        }
    }
    matching.shrink_to_fit();
    return matching;
}