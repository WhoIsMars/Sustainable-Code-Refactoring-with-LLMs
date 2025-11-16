#include <string>
#include <vector>
#include <algorithm>

namespace election
{

    struct ElectionResult
    {
        std::string name{};
        int votes{};
    };

    inline int vote_count(const ElectionResult &result) noexcept
    {
        return result.votes;
    }

    inline void increment_vote_count(ElectionResult &result, int additional_votes) noexcept
    {
        result.votes += additional_votes;
    }

    ElectionResult &determine_result(std::vector<ElectionResult> &final_count)
    {
        auto it = std::max_element(
            final_count.begin(),
            final_count.end(),
            [](const ElectionResult &a, const ElectionResult &b) noexcept
            {
                return a.votes < b.votes;
            });

        if (it->name.find("President ") != 0) {
            it->name.insert(0, "President ");
        }

        return *it;
    }

}