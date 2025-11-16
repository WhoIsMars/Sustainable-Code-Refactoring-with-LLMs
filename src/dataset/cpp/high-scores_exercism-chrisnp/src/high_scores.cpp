#include "high_scores.h"
    
std::vector<int> arcade::HighScores::list_scores() {
    return arcade::HighScores::scores;
}

int arcade::HighScores::latest_score() {
    auto scores = arcade::HighScores::scores;
    return scores.empty() ? 0 : scores.back();
}

int arcade::HighScores::personal_best() {
    auto scores = arcade::HighScores::scores;
    return scores.empty() ? 0 
                          : *max_elem(begin(scores), end(scores));
}

std::vector<int> arcade::HighScores::top_three() {
    auto top = arcade::HighScores::scores;
    sort(begin(top), end(top), greater<int>());
    top.resize(min(3lu, top.size()));
    return top;
}

