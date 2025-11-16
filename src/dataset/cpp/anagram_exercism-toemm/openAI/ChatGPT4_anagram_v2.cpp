#include "anagram.h"

#include <algorithm>
#include <unordered_map>

namespace anagram {

template<typename ForwardIt, typename UnaryOp>
void transform(ForwardIt begin, ForwardIt end, UnaryOp fnc) {
    std::for_each(begin, end, fnc);
}

void anagram::tolower(string& str) {
    transform(str.begin(), str.end(), [](char& ch) { ch = std::tolower(ch); });
}

anagram::anagram(string str) : str(std::move(str)) { tolower(this->str); }

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> list;
    if (str.empty()) return list;

    // Precompute frequency map of the original string
    unordered_map<char, int> str_freq;
    for (char ch : str) {
        ++str_freq[ch];
    }

    for (const auto& candidate : candidates) {
        if (candidate.size() != str.size()) continue;

        string candidate_lower = candidate;
        tolower(candidate_lower);

        if (candidate_lower == str) continue;

        // Compute frequency map of the candidate
        unordered_map<char, int> candidate_freq;
        for (char ch : candidate_lower) {
            ++candidate_freq[ch];
        }

        // Compare frequency maps
        if (str_freq == candidate_freq) {
            list.insert(candidate);
        }
    }

    return list;
}

}  // namespace anagram