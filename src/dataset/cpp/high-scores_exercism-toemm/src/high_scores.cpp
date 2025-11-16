#include "high_scores.h"

#include <algorithm>

namespace arcade {

std::vector<int> HighScores::list_scores() {
    // TODO: Return all scores for this session.
    return scores;
}

int HighScores::latest_score() {
    // TODO: Return the latest score for this session.
    return *(scores.end()-1);
}

int HighScores::personal_best() {

    return *std::max_element(scores.begin(), scores.end());
}

std::vector<int> HighScores::top_three() {
    
    // TODO: Return the top 3 scores for this session in descending order.
    std::vector<int> results(scores.size() < 3 ? scores.size() : 3);
    std::partial_sort_copy(scores.begin(), scores.end(), results.begin(), results.end(),
                            [] (auto a, auto b) 
                                { 
                                    return a > b; 
                                });

    return results;
}

}  // namespace arcade
