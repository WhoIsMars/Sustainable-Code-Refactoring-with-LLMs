#include "queen_attack.h"
#include <array>

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
  int col_diff = white_position.first - black_position.first;
  int row_diff = white_position.second - black_position.second;
  return col_diff == 0 || row_diff == 0 || abs(col_diff) == abs(row_diff);
}

unsigned chess_board::get_queen_position_in_string(Position coordinates) const {
  return coordinates.first * 16 + coordinates.second * 2;
}

chess_board::operator string() const {
  std::array<char, 128> board;
  board.fill('_');
  for (int i = 1; i < 128; i += 16) board[i] = '\n';

  board[get_queen_position_in_string(white_position)] = 'W';
  board[get_queen_position_in_string(black_position)] = 'B';

  return string(board.data(), board.size());
}
}  // namespace queen_attack