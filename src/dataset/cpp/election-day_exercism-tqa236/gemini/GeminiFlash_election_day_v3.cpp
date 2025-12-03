#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

namespace election
{

    struct ElectionResult
    {
        std::string name{};
        int votes{};
    };

    int vote_count(const ElectionResult &result)
    {
        return result.votes;
    }

    void increment_vote_count(ElectionResult &result, int additional_votes)
    {
        result.votes += additional_votes;
    }

    ElectionResult &determine_result(std::vector<ElectionResult> &final_count)
    {
        if (final_count.empty()) {
            static ElectionResult empty_result{"", 0};
            return empty_result;
        }

        ElectionResult* winner = &final_count[0];
        for (size_t i = 1; i < final_count.size(); ++i) {
            if (final_count[i].votes > winner->votes) {
                winner = &final_count[i];
            }
        }

        winner->name.reserve(winner->name.size() + 10);
        winner->name = "President " + winner->name;

        return *winner;
    }

} // namespace election