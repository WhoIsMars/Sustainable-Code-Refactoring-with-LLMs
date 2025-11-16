#include "queen_attack.h"

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

unsigned chess_board::get_queen_position_in_string(Position coordinates) const {
  return coordinates.first * 16 + coordinates.second * 2;
}

chess_board::operator string() const {
  string board(127, '_');
  for (int i = 15; i < 127; i += 16) board[i] = '\n';

  board[get_queen_position_in_string(white_position)] = 'W';
  board[get_queen_position_in_string(black_position)] = 'B';

  return board;
}
}  // namespace queen_attack