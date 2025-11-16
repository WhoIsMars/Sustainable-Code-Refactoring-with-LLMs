#include <string>
#include <vector>

namespace election {

// The election result struct is already created for you:

struct ElectionResult {
    // Name of the candidate
    std::string name{};
    // Number of votes the candidate has
    int votes{};
};

// TODO: Task 1
int vote_count(ElectionResult& res) {
    return res.votes;
}

// TODO: Task 2
void increment_vote_count(ElectionResult& res, int num) {
    res.votes += num;
}

// TODO: Task 3
// determine_result receives the reference to a final_count and returns a
// reference to the `ElectionResult` of the new president. It also changes the
// name of the winner by prefixing it with "President". The final count is given
// in the form of a `reference` to `std::vector<ElectionResult>`, a vector with
// `ElectionResults` of all the participating candidates.
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