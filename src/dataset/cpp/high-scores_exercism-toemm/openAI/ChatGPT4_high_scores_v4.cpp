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
    std::vector<int> results;
    results.reserve(3);
    std::partial_sort(scores.begin(), scores.begin() + std::min(3, static_cast<int>(scores.size())), scores.end(), std::greater<>());
    results.insert(results.end(), scores.begin(), scores.begin() + std::min(3, static_cast<int>(scores.size())));
    return results;
}

}  // namespace arcade