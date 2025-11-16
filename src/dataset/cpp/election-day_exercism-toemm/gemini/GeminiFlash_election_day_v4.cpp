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
        static ElectionResult empty_result{"", 0};
        return empty_result;
    }

    auto winner_it = std::max_element(results_list.begin(), results_list.end(),
                                      [](const ElectionResult& a, const ElectionResult& b) {
                                          return a.votes < b.votes;
                                      });

    winner_it->name = "President " + winner_it->name;
    return *winner_it;
}

}  // namespace election