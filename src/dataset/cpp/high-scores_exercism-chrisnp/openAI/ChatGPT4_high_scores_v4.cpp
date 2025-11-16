#include "high_scores.h"
#include <algorithm>

std::vector<int> arcade::HighScores::list_scores() {
    return scores;
}

int arcade::HighScores::latest_score() {
    return scores.empty() ? 0 : scores.back();
}

int arcade::HighScores::personal_best() {
    return scores.empty() ? 0 : *std::max_element(scores.cbegin(), scores.cend());
}

std::vector<int> arcade::HighScores::top_three() {
    if (scores.empty()) return {};
    std::vector<int> top = scores;
    std::partial_sort(top.begin(), top.begin() + std::min(3ul, top.size()), top.end(), std::greater<int>());
    top.resize(std::min(3ul, top.size()));
    return top;
}