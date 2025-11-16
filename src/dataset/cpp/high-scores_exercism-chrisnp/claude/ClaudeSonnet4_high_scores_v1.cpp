#include "high_scores.h"
    
std::vector<int> arcade::HighScores::list_scores() {
    return arcade::HighScores::scores;
}

int arcade::HighScores::latest_score() {
    return arcade::HighScores::scores.empty() ? 0 : arcade::HighScores::scores.back();
}

int arcade::HighScores::personal_best() {
    return arcade::HighScores::scores.empty() ? 0 
                          : *std::max_element(arcade::HighScores::scores.begin(), arcade::HighScores::scores.end());
}

std::vector<int> arcade::HighScores::top_three() {
    if (arcade::HighScores::scores.empty()) {
        return {};
    }
    
    std::vector<int> top = arcade::HighScores::scores;
    std::partial_sort(top.begin(), top.begin() + std::min(3ul, top.size()), top.end(), std::greater<int>());
    top.resize(std::min(3ul, top.size()));
    return top;
}