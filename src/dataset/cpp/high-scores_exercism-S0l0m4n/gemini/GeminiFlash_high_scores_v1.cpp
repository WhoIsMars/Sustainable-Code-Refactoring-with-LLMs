#include "high_scores.h"

#include <algorithm>
#include <vector>
#include <limits> // Required for numeric_limits

namespace arcade {

    std::vector<int> HighScores::list_scores() {
        // Return all scores for this session.
        return scores;
    }

    int HighScores::latest_score() {
        // Return the latest score for this session.
        return scores.empty() ? 0 : scores.back(); // Handle empty case
    }

    int HighScores::personal_best() {
        // Return the highest score for this session.
        if (scores.empty()) {
            return 0; // Or throw an exception, depending on desired behavior for empty scores
        }
        return *std::max_element(scores.begin(), scores.end());
    }

    std::vector<int> HighScores::top_three() {
        // Return the top 3 scores for this session in descending order.
        std::vector<int> top_scores = scores;
        std::sort(top_scores.begin(), top_scores.end(), std::greater<int>());
        top_scores.resize(std::min(3, (int)top_scores.size())); // Ensure size is not greater than 3
        return top_scores;
    }

}  // namespace arcade