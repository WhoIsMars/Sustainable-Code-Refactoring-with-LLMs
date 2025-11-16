#include <string>
#include <vector>
#include <algorithm>

template<class ForwardIt, class Compare>
constexpr auto max_elem(ForwardIt first, ForwardIt last, Compare comp) -> ForwardIt {
    return std::max_element(first, last, comp);
}

namespace election {

struct ElectionResult {
    std::string name {};
    int votes {0};
};

// Task 1
constexpr auto vote_count(const ElectionResult& candidate) noexcept -> int {
    return candidate.votes;
}

// Task 2
inline void increment_vote_count(ElectionResult& candidate, int votes) noexcept {
    candidate.votes += votes;
}

// Task 3
auto determine_result(std::vector<ElectionResult>& final_count) -> ElectionResult& {
    auto ballot_outcome = std::max_element(final_count.begin(), final_count.end(), 
                                           [](const auto& cand1, const auto& cand2) { 
                                               return cand1.votes < cand2.votes; 
                                           });
    ballot_outcome->name.insert(0, "President ");
    return *ballot_outcome;
}

}  // namespace election

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif