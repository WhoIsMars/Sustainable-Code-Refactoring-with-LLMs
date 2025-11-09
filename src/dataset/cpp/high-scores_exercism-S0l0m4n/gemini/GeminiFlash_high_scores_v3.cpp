#include "high_scores.h"

#include <algorithm>
#include <vector>
#include <limits>

namespace arcade {

    std::vector<int> HighScores::list_scores() {
        return scores;
    }

    int HighScores::latest_score() {
        return scores.empty() ? 0 : scores.back();
    }

    int HighScores::personal_best() {
        if (scores.empty()) {
            return 0;
        }
        return *std::max_element(scores.begin(), scores.end());
    }

    std::vector<int> HighScores::top_three() {
        std::vector<int> top_scores;
        size_t count = std::min(scores.size(), (size_t)3);

        if (count == 0) return {};

        std::vector<int> sorted_scores = scores;
        std::partial_sort(sorted_scores.begin(), sorted_scores.begin() + count, sorted_scores.end(), std::greater<int>());

        for (size_t i = 0; i < count; ++i) {
            top_scores.push_back(sorted_scores[i]);
        }

        return top_scores;
    }

}  // namespace arcade