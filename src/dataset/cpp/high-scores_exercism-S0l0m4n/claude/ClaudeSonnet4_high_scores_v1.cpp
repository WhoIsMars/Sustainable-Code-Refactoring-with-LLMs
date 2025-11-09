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
        
        // Use partial_sort for optimal performance with 3 elements
        std::vector<int> temp(scores);
        const size_t n = std::min(size, static_cast<size_t>(3));
        std::partial_sort(temp.begin(), temp.begin() + n, temp.end(), std::greater<int>());
        
        return std::vector<int>(temp.begin(), temp.begin() + n);
    }

}  // namespace arcade