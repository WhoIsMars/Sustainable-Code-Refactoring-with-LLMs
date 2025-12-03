#include "high_scores.h"

#include <algorithm>
#include <vector>

namespace arcade {

    std::vector<int> HighScores::list_scores() {
        // Return all scores for this session.
        return scores;
    }

    int HighScores::latest_score() {
        // Return the latest score for this session.
        return scores.empty() ? 0 : scores.back();
    }

    int HighScores::personal_best() {
        // Return the highest score for this session.
        if (scores.empty()) return 0;
        return *std::max_element(scores.begin(), scores.end());
    }

    std::vector<int> HighScores::top_three() {
        // Return the top 3 scores for this session in descending order.
        std::vector<int> top_scores = scores;
        std::sort(top_scores.begin(), top_scores.end(), std::greater<int>());
        top_scores.resize(std::min<size_t>(3, top_scores.size()));
        return top_scores;
    }

}  // namespace arcade