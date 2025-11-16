#include <string>
#include <vector>
#include <algorithm>

namespace election {

struct ElectionResult {
    std::string name {};
    int votes {0};
};

auto vote_count(const ElectionResult& candidate) noexcept -> int {
    return candidate.votes;
}

void increment_vote_count(ElectionResult& candidate, const int votes) noexcept {
    candidate.votes += votes;
}

auto determine_result(std::vector<ElectionResult>& final_count) -> ElectionResult& {
    auto ballot_outcome = std::max_element(final_count.begin(), final_count.end(), 
                                          [](const auto& cand1, const auto& cand2) noexcept { 
                                            return cand1.votes < cand2.votes; 
                                          });
    ballot_outcome->name.reserve(ballot_outcome->name.size() + 10);
    ballot_outcome->name.insert(0, "President ");
    return *ballot_outcome;
}

}  // namespace election

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif