#include "queen_attack.h"

#include <utility>
#include <stdexcept>
#include <cmath>

namespace queen_attack {

chess_board::chess_board(std::pair<int, int> white, std::pair<int, int> black)
    : white_(std::move(white)), black_(std::move(black)) {
    check();
}

const std::pair<int, int>& chess_board::white() const {
    return white_;
}

const std::pair<int, int>& chess_board::black() const {
    return black_;
}

bool chess_board::can_attack() const {
    // Check horizontal, vertical, and diagonal in one condition
    return white_.first == black_.first || 
           white_.second == black_.second || 
           std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second);
}

void chess_board::check() const {
    if (white_.first < 0 || white_.second < 0 || black_.first < 0 || black_.second < 0 || 
        white_.first >= 8 || white_.second >= 8 || 
        black_.first >= 8 || black_.second >= 8 || 
        white_ == black_) {
        throw std::domain_error("Invalid queen position.");
    }
}

}  // namespace queen_attack