#include "high_scores.h"

#include <algorithm>

namespace arcade {

std::vector<int> HighScores::list_scores() {
    return scores;
}

int HighScores::latest_score() {
    return scores.back();
}

int HighScores::personal_best() {
    return *std::max_element(scores.begin(), scores.end());
}

std::vector<int> HighScores::top_three() {
    std::vector<int> results = scores;
    std::nth_element(results.begin(), results.begin() + std::min(3, (int)results.size()), results.end(), std::greater<>());
    results.resize(std::min(3, (int)results.size()));
    std::sort(results.begin(), results.end(), std::greater<>());
    return results;
}

}  // namespace arcade