#include "high_scores.h"

#include <algorithm>

namespace arcade {

    const std::vector<int>& HighScores::list_scores() {
        return scores;
    }

    int HighScores::latest_score() {
        return scores.back();
    }

    int HighScores::personal_best() {
        return *std::max_element(scores.begin(), scores.end());
    }

    std::vector<int> HighScores::top_three() {
        if (scores.empty()) {
            return {};
        }
        
        std::vector<int> top_scores = scores;
        std::partial_sort(top_scores.begin(), 
                         top_scores.begin() + std::min(3UL, top_scores.size()), 
                         top_scores.end(), 
                         std::greater<int>());
        
        top_scores.resize(std::min(3UL, top_scores.size()));
        return top_scores;
    }

}  // namespace arcade