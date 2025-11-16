#include "queen_attack.h"

#include <iostream>
#include <stdexcept>
#include <cmath> // Required for std::abs

namespace queen_attack {

chess_board::chess_board(position white, position black) : m_white(white), m_black(black) {
  if (white == black) {
    throw std::domain_error("Black and white positions cannot be the same.");
  }
}

position chess_board::white() const { return m_white; }

position chess_board::black() const { return m_black; }

bool chess_board::can_attack() const {
  int row_diff = m_white.first - m_black.first;
  int col_diff = m_white.second - m_black.second;

  return row_diff == 0 || col_diff == 0 || std::abs(row_diff) == std::abs(col_diff);
}

chess_board::operator std::string() const {
  static const std::string row = "_ _ _ _ _ _ _ _\n";
  std::string board;
  board.reserve(128); // Pre-allocate memory for the entire board string

  for (int i = 0; i < 8; ++i) {
    board += row;
  }

  board[m_white.first * 16 + m_white.second * 2] = 'W';
  board[m_black.first * 16 + m_black.second * 2] = 'B';

  return board;
}

} // namespace queen_attack