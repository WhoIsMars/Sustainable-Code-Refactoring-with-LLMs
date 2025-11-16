#include <string>
#include <vector>

template<class ForwardIt, class Compare>
constexpr auto max_elem(ForwardIt first, ForwardIt last, Compare comp) -> ForwardIt {
    if (first == last) return last;
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first) if (comp(*largest, *first)) largest = first;
    return largest;
}

namespace election {

struct ElectionResult {
    // Name of the candidate
    std::string name {};
    // Number of votes the candidate has
    int votes {0};
};
// Task 1
auto vote_count(ElectionResult& candidate) noexcept -> int {
    return candidate.votes;
}
// Task 2
void increment_vote_count(ElectionResult& candidate, const int &votes) {
    candidate.votes += votes;
}
// Task 3
auto determine_result(std::vector<ElectionResult> &final_count) -> ElectionResult& {
    const auto& ballot_outcome = max_elem(begin(final_count), end(final_count), 
                                          [](auto& cand1, auto& cand2) { 
                                            return cand1.votes < cand2.votes; 
                                          });
    ballot_outcome->name.insert(0, "President ");
    return *ballot_outcome;
}

}  // namespace election



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif