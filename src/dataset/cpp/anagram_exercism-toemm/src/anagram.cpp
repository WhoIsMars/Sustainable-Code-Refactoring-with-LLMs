#include "anagram.h"

#include <iostream>

namespace anagram {

template<typename ForwardIt, typename EndIt, typename DestIt, typename UnaryOp>
DestIt transform(ForwardIt begin, EndIt end, DestIt destination, UnaryOp fnc) {

    for (; begin != end; begin++, destination++) {
        *destination = fnc(*begin);
    }

    return destination;
}

void anagram::tolower(string& str) {
    transform(str.begin(), str.end(), str.begin(), 
    [] (auto ch) {return std::tolower(ch); });
}

anagram::anagram(string str) : str(std::move(str)) { tolower(this->str); }

unordered_set<string> anagram::matches(const unordered_set<string>& candidates) {
    unordered_set<string> list;
    auto str_size = str.size();


    for (const auto& candidate : candidates) {

        auto str_copy = str;
        auto candidate_lower = candidate;
        tolower(candidate_lower);

        // next candidate if candidate equals string or is not equal length
        if (candidate.size() != str_size) continue;
        if (candidate_lower == str) continue;
 
        for (char ch : candidate_lower) {

            auto pos = str_copy.find(ch);

            if (pos != std::string::npos) {
                str_copy.erase(pos, 1);
            } else {
                break;
            }

        }


        if (str_copy.empty()) { 
            //std::cout << candidate << endl; 
            list.insert(candidate);
        };


    }


    return list;


}


}  // namespace anagram
