#include <string>
#include <vector>
#include <algorithm>

namespace election {

struct ElectionResult {
    std::string name{};
    int votes{};
};

int vote_count(ElectionResult& res) {
    return res.votes;
}

void increment_vote_count(ElectionResult& res, int num) {
    res.votes += num;
}

ElectionResult& determine_result(std::vector<ElectionResult>& results_list) {
    if (results_list.empty()) {
        static ElectionResult dummy_result{"", 0};
        return dummy_result;
    }

    ElectionResult* winner = &results_list[0];
    for (size_t i = 1; i < results_list.size(); ++i) {
        if (results_list[i].votes > winner->votes) {
            winner = &results_list[i];
        }
    }

    winner->name = "President " + winner->name;
    return *winner;
}

}  // namespace election