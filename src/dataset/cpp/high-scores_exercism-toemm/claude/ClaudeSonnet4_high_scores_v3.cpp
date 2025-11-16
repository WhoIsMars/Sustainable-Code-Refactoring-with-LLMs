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
    const size_t result_size = std::min(scores.size(), size_t{3});
    std::vector<int> results;
    results.reserve(result_size);
    
    std::partial_sort_copy(scores.begin(), scores.end(), 
                          std::back_inserter(results), 
                          results.begin() + result_size,
                          std::greater<int>());
    
    return results;
}

}  // namespace arcade