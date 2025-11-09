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

int vote_count(ElectionResult& result) {
    return result.votes;
}

void increment_vote_count(ElectionResult& result, int extra_votes) {
    result.votes += extra_votes;
}

ElectionResult& determine_result(vector<ElectionResult>& results) {
    if (results.empty()) {
        static ElectionResult empty_result{"", 0};
        return empty_result;
    }

    ElectionResult* winner = &results[0];
    for (size_t i = 1; i < results.size(); ++i) {
        if (results[i].votes > winner->votes) {
            winner = &results[i];
        }
    }

    winner->name.reserve(winner->name.length() + 10);
    winner->name = "President " + winner->name;
    return *winner;
}

}  // namespace election