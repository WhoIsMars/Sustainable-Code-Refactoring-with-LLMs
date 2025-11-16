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

anagram::anagram(string str) : str(std::move(str)) {
    tolower(this->str);
    std::sort(this->str.begin(), this->str.end());
}

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> list;
    auto str_size = str.size();

    for (const auto& candidate : candidates) {
        if (candidate.size() != str_size) continue;

        string candidate_lower = candidate;
        tolower(candidate_lower);

        if (candidate_lower == str) continue;

        string sorted_candidate = candidate_lower;
        std::sort(sorted_candidate.begin(), sorted_candidate.end());

        if (sorted_candidate == str) {
            list.insert(candidate);
        }
    }

    return list;
}

}  // namespace anagram