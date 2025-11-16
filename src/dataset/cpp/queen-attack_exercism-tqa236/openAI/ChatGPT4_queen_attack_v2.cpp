#include "queen_attack.h"
#include <sstream>

namespace queen_attack {
chess_board::chess_board() = default;

chess_board::chess_board(Position white, Position black)
    : white_position{white}, black_position{black} {
  if (white_position == black_position) {
    throw domain_error("Queen positions must be distinct.");
  }
}

Position chess_board::white() const { return white_position; }

Position chess_board::black() const { return black_position; }

bool chess_board::can_attack() const {
  return white_position.first == black_position.first || 
         white_position.second == black_position.second || 
         abs(white_position.first - black_position.first) == abs(white_position.second - black_position.second);
}

chess_board::operator string() const {
  std::ostringstream board;
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      if (white_position == Position{row, col}) {
        board << 'W';
      } else if (black_position == Position{row, col}) {
        board << 'B';
      } else {
        board << '_';
      }
      if (col < 7) board << ' ';
    }
    board << '\n';
  }
  return board.str();
}
}  // namespace queen_attack