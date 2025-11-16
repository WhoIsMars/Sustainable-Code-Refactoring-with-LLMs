#include "queen_attack.h"

#include <utility>
#include <stdexcept>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_(white), black_(black) {
    if (white_.first < 0 || white_.second < 0 || black_.first < 0 || black_.second < 0 
        || white_.first >= 8 || white_.second >= 8 
        || black_.first >= 8 || black_.second >= 8) 
        throw std::domain_error("Queen position invalid.");

    if (white_ == black_) throw std::domain_error("Same pos");
}

const std::pair<int, int> chess_board::white() const {
    return white_;
}

const std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // check horizontal and vertical first
    if (white_.first == black_.first ||
        white_.second == black_.second) return true;

    // check diagonal using absolute difference
    const int delta_column = (white_.first > black_.first) ? 
        white_.first - black_.first : black_.first - white_.first;
    const int delta_row = (white_.second > black_.second) ? 
        white_.second - black_.second : black_.second - white_.second;

    return delta_column == delta_row;
}

void chess_board::check() const {
    if (white_.first < 0 || white_.second < 0 || black_.first < 0 || black_.second < 0 
        || white_.first >= 8 || white_.second >= 8 
        || black_.first >= 8 || black_.second >= 8) 
        throw std::domain_error("Queen position invalid.");

    if (white_ == black_) throw std::domain_error("Same pos");  
}

}  // namespace queen_attack