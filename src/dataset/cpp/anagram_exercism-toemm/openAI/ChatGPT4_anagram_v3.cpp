#include "anagram.h"

#include <algorithm>
#include <unordered_map>

namespace anagram {

template<typename ForwardIt, typename EndIt, typename DestIt, typename UnaryOp>
DestIt transform(ForwardIt begin, EndIt end, DestIt destination, UnaryOp fnc) {
    while (begin != end) {
        *destination++ = fnc(*begin++);
    }
    return destination;
}

void anagram::tolower(string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) { return std::tolower(ch); });
}

anagram::anagram(string str) : str(std::move(str)) { tolower(this->str); }

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> list;
    if (str.empty()) return list;

    std::unordered_map<char, int> str_char_count;
    for (char ch : str) {
        str_char_count[ch]++;
    }

    for (const auto& candidate : candidates) {
        if (candidate.size() != str.size()) continue;

        string candidate_lower = candidate;
        tolower(candidate_lower);
        if (candidate_lower == str) continue;

        std::unordered_map<char, int> candidate_char_count;
        for (char ch : candidate_lower) {
            candidate_char_count[ch]++;
        }

        if (candidate_char_count == str_char_count) {
            list.insert(candidate);
        }
    }

    return list;
}

}  // namespace anagram