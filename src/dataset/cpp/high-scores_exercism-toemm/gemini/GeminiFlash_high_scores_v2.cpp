#include "high_scores.h"

#include <algorithm>
#include <limits>

namespace arcade {

std::vector<int> HighScores::list_scores() const {
    return scores;
}

int HighScores::latest_score() const {
    if (scores.empty()) {
        return 0; // Or throw an exception, depending on desired behavior for empty scores
    }
    return scores.back();
}

int HighScores::personal_best() const {
    if (scores.empty()) {
        return 0; // Or return a more appropriate default value, like std::numeric_limits<int>::min();
    }
    return *std::max_element(scores.cbegin(), scores.cend());
}

std::vector<int> HighScores::top_three() const {
    std::vector<int> results;
    size_t count = std::min(scores.size(), static_cast<size_t>(3));
    results.reserve(count);

    std::vector<int> temp_scores = scores; // Create a copy to avoid modifying the original

    std::partial_sort(temp_scores.begin(), temp_scores.begin() + count, temp_scores.end(), std::greater<int>());

    results.insert(results.end(), temp_scores.begin(), temp_scores.begin() + count);


    return results;
}

}  // namespace arcade