#include "high_scores.h"

#include <algorithm>
#include <limits>

namespace arcade {

std::vector<int> HighScores::list_scores() {
    return scores;
}

int HighScores::latest_score() {
    if (scores.empty()) {
        return 0; // Or throw an exception, depending on desired behavior for empty scores
    }
    return scores.back();
}

int HighScores::personal_best() {
    if (scores.empty()) {
        return std::numeric_limits<int>::min(); // Or throw an exception
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
    std::vector<int> results;
    size_t count = std::min(scores.size(), (size_t)3);
    results.reserve(count);

    std::vector<int> temp_scores = scores; // Create a copy to avoid modifying the original

    std::sort(temp_scores.begin(), temp_scores.end(), std::greater<int>());

    for (size_t i = 0; i < count; ++i) {
        results.push_back(temp_scores[i]);
    }

    return results;
}

}  // namespace arcade