#include "high_scores.h"
#include <algorithm>

std::vector<int> arcade::HighScores::list_scores() {
    return scores; // Directly return the member variable
}

int arcade::HighScores::latest_score() {
    return scores.empty() ? 0 : scores.back(); // Avoid unnecessary copy
}

int arcade::HighScores::personal_best() {
    return scores.empty() ? 0 : *std::max_element(scores.begin(), scores.end()); // Use std::max_element directly
}

std::vector<int> arcade::HighScores::top_three() {
    if (scores.empty()) return {}; // Handle empty case early
    std::vector<int> top = scores; // Copy only once
    std::partial_sort(top.begin(), top.begin() + std::min(3lu, top.size()), top.end(), std::greater<int>()); // Use partial_sort for efficiency
    top.resize(std::min(3lu, top.size())); // Resize after sorting
    return top;
}