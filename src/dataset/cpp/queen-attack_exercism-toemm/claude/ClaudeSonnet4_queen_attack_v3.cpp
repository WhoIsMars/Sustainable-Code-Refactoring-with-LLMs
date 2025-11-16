#include "queen_attack.h"

#include <utility>
#include <stdexcept>
#include <cstdlib>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_(white), black_(black) {
    check();
}

const std::pair<int, int> chess_board::white() const {
    return white_;
}

const std::pair<int, int> chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    if (white_.first == black_.first || white_.second == black_.second) {
        return true;
    }
    
    return std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

void chess_board::check() const {
    if ((white_.first | white_.second | black_.first | black_.second) < 0 ||
        (white_.first | white_.second | black_.first | black_.second) >= 8) {
        throw std::domain_error("Queen position invalid.");
    }
    
    if (white_ == black_) {
        throw std::domain_error("Same pos");
    }
}

}  // namespace queen_attack