#include "high_scores.h"
#include <algorithm>
#include <limits>

std::vector<int> arcade::HighScores::list_scores() {
    return scores;
}

int arcade::HighScores::latest_score() {
    return scores.empty() ? 0 : scores.back();
}

int arcade::HighScores::personal_best() {
    if (scores.empty()) return 0;
    return *std::max_element(scores.begin(), scores.end());
}

std::vector<int> arcade::HighScores::top_three() {
    if (scores.empty()) return {};
    std::vector<int> top(scores);
    std::partial_sort(top.begin(), top.begin() + std::min(3lu, top.size()), top.end(), std::greater<int>());
    top.resize(std::min(3lu, top.size()));
    return top;
}