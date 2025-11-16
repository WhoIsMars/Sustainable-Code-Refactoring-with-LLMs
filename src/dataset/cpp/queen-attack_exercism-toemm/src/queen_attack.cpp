#include "queen_attack.h"

#include <utility>
#include <stdexcept>

namespace queen_attack {



chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_(white), black_(black) {
        check();
    }

const std::pair<int, int> chess_board::white() const {
    return this->white_;

}
const std::pair<int, int> chess_board::black() const {
    return this->black_;
}

bool chess_board::can_attack() const {


    // check horizontal and vertical first
    if (white_.first == black_.first ||
        white_.second == black_.second) return true;


    // check diagonal
    int delta_column = white_.first - black_.first;
    if (delta_column < 0) delta_column *= -1;

    int delta_row = white_.second - black_.second;
    if (delta_row < 0) delta_row *= -1;

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
