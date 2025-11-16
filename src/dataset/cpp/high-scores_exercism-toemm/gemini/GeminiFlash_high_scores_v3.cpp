#include "high_scores.h"

#include <algorithm>
#include <limits>

namespace arcade {

std::vector<int> HighScores::list_scores() {
    return scores;
}

int HighScores::latest_score() {
    if (scores.empty()) {
        return 0; 
    }
    return scores.back();
}

int HighScores::personal_best() {
    if (scores.empty()) {
        return 0;
    }
    int best = scores[0];
    for (size_t i = 1; i < scores.size(); ++i) {
        if (scores[i] > best) {
            best = scores[i];
        }
    }
    return best;
}

std::vector<int> HighScores::top_three() {
    size_t count = std::min(scores.size(), static_cast<size_t>(3));
    std::vector<int> results(count);

    if (count == 0) {
        return results;
    }

    std::vector<int> temp_scores = scores;
    std::partial_sort(temp_scores.begin(), temp_scores.begin() + count, temp_scores.end(), std::greater<int>());

    for (size_t i = 0; i < count; ++i) {
        results[i] = temp_scores[i];
    }

    return results;
}

}  // namespace arcade