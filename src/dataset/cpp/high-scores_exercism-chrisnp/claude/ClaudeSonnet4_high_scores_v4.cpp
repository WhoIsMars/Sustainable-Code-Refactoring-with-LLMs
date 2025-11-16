#include "high_scores.h"
#include <algorithm>

std::vector<int> arcade::HighScores::list_scores() {
    return scores;
}

int arcade::HighScores::latest_score() {
    return scores.empty() ? 0 : scores.back();
}

int arcade::HighScores::personal_best() {
    if (scores.empty()) return 0;
    return *std::max_element(scores.cbegin(), scores.cend());
}

std::vector<int> arcade::HighScores::top_three() {
    if (scores.empty()) return {};
    
    std::vector<int> top;
    top.reserve(std::min(3ul, scores.size()));
    
    std::partial_sort_copy(scores.cbegin(), scores.cend(),
                          std::back_inserter(top), top.end() + std::min(3ul, scores.size()),
                          std::greater<int>());
    
    return top;
}