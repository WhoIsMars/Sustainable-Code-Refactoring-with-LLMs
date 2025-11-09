#include <string>
#include <vector>
#include <algorithm>

namespace election {

using std::string;
using std::vector;

// The election result struct is already created for you:
struct ElectionResult {
    // Name of the candidate
    std::string name{};
    // Number of votes the candidate has
    int votes{};
};

// Task 1
int vote_count(const ElectionResult& result) {
    return result.votes;
}

// Task 2
void increment_vote_count(ElectionResult& result, int extra_votes) {
    result.votes += extra_votes;
}

// Task 3
ElectionResult& determine_result(vector<ElectionResult>& results) {
    auto winner = std::max_element(results.begin(), results.end(), 
                                   [](const ElectionResult& a, const ElectionResult& b) {
                                       return a.votes < b.votes;
                                   });
    winner->name.insert(0, "President ");
    return *winner;
}

}  // namespace election