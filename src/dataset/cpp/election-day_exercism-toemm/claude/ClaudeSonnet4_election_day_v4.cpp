#include <string>
#include <vector>

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
    int highest_vote_count = 0;
    size_t winner_index = 0;

    for (size_t i = 0; i < results_list.size(); ++i) {
        if (results_list[i].votes > highest_vote_count) {
            highest_vote_count = results_list[i].votes;
            winner_index = i;
        }
    }

    results_list[winner_index].name.insert(0, "President ");
    return results_list[winner_index];
}

}  // namespace election