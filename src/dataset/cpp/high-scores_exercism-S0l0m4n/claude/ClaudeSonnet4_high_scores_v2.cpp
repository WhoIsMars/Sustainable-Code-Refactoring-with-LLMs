#include "high_scores.h"

#include <algorithm>

namespace arcade {

    const std::vector<int>& HighScores::list_scores() {
        // Return all scores for this session.
        return scores;
    }

    int HighScores::latest_score() {
        // Return the latest score for this session.
        return scores.back();
    }

    int HighScores::personal_best() {
        // Return the highest score for this session.
        return *std::max_element(scores.begin(), scores.end());
    }

    std::vector<int> HighScores::top_three() {
        // Return the top 3 scores for this session in descending order.
        const size_t size = scores.size();
        if (size == 0)
            return {};
        if (size == 1)
            return { scores[0] };
        if (size == 2) {
            return scores[0] > scores[1] ? 
                std::vector<int>{ scores[0], scores[1] } : 
                std::vector<int>{ scores[1], scores[0] };
        }
        
        // Use partial_sort for better performance with large datasets
        std::vector<int> temp_scores = scores;
        const size_t top_count = std::min(size, size_t(3));
        std::partial_sort(temp_scores.begin(), temp_scores.begin() + top_count, temp_scores.end(), std::greater<int>());
        
        temp_scores.resize(top_count);
        return temp_scores;
    }

}  // namespace arcade