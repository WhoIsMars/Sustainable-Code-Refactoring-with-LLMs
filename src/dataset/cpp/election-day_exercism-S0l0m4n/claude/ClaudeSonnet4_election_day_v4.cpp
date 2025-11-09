#include <string>
#include <vector>

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
    ElectionResult* winner = &results[0];
    for (auto& result : results) {
        if (result.votes > winner->votes) {
            winner = &result;
        }
    }
    winner->name.insert(0, "President ");
    return *winner;
}

}  // namespace election