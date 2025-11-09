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
        const size_t size = scores.size();
        if (size == 0) return {};
        if (size == 1) return {scores[0]};
        if (size == 2) {
            return scores[0] > scores[1] ? 
                std::vector<int>{scores[0], scores[1]} : 
                std::vector<int>{scores[1], scores[0]};
        }

        std::vector<int> top_scores(scores.begin(), scores.begin() + 3);
        std::sort(top_scores.rbegin(), top_scores.rend());

        for (size_t i = 3; i < size; ++i) {
            if (scores[i] > top_scores[2]) {
                top_scores[2] = scores[i];
                if (top_scores[2] > top_scores[1]) {
                    std::swap(top_scores[1], top_scores[2]);
                    if (top_scores[1] > top_scores[0]) {
                        std::swap(top_scores[0], top_scores[1]);
                    }
                }
            }
        }
        return top_scores;
    }

}  // namespace arcade