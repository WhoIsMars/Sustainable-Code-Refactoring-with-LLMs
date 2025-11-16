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
  const auto col_diff = abs(white_position.first - black_position.first);
  const auto row_diff = abs(white_position.second - black_position.second);
  return col_diff == 0 || row_diff == 0 || col_diff == row_diff;
}

chess_board::operator string() const {
  string board(64, '_');
  board[white_position.first * 8 + white_position.second] = 'W';
  board[black_position.first * 8 + black_position.second] = 'B';

  string formatted_board;
  for (size_t i = 0; i < 64; i += 8) {
    formatted_board.append(board.begin() + i, board.begin() + i + 8);
    formatted_board.append("\n");
  }
  return formatted_board;
}
}  // namespace queen_attack