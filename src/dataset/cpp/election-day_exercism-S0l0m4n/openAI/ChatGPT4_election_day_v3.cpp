#include <string>
#include <vector>
#include <algorithm>

namespace election {

using std::string;
using std::vector;

struct ElectionResult {
    std::string name{};
    int votes{};
};

int vote_count(const ElectionResult& result) {
    return result.votes;
}

void increment_vote_count(ElectionResult& result, int extra_votes) {
    result.votes += extra_votes;
}

ElectionResult& determine_result(vector<ElectionResult>& results) {
    auto winner = std::max_element(results.begin(), results.end(), 
                                   [](const ElectionResult& a, const ElectionResult& b) {
                                       return a.votes < b.votes;
                                   });
    winner->name = "President " + winner->name;
    return *winner;
}

}  // namespace election