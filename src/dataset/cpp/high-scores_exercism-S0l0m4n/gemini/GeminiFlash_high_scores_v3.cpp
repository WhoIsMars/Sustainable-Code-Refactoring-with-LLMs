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
        if (scores.empty()) {
            return {};
        }

        std::vector<int> top_scores = scores;
        std::sort(top_scores.begin(), top_scores.end(), std::greater<int>());

        std::vector<int> result;
        size_t count = std::min(static_cast<size_t>(3), top_scores.size());
        for (size_t i = 0; i < count; ++i) {
            result.push_back(top_scores[i]);
        }

        return result;
    }

}  // namespace arcade