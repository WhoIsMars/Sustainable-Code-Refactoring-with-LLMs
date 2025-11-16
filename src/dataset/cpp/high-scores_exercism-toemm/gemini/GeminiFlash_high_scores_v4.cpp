#include "high_scores.h"

#include <algorithm>
#include <limits>

namespace arcade {

std::vector<int> HighScores::list_scores() {
    return scores;
}

int HighScores::latest_score() {
    return scores.back();
}

int HighScores::personal_best() {
    if (scores.empty()) {
        return std::numeric_limits<int>::min();
    }
    return *std::max_element(scores.begin(), scores.end());
}

std::vector<int> HighScores::top_three() {
    std::vector<int> top;
    size_t count = std::min(static_cast<size_t>(3), scores.size());
    top.reserve(count);

    std::vector<int> temp_scores = scores;
    std::partial_sort(temp_scores.begin(), temp_scores.begin() + count, temp_scores.end(), std::greater<int>());

    for (size_t i = 0; i < count; ++i) {
        top.push_back(temp_scores[i]);
    }

    return top;
}

}  // namespace arcade