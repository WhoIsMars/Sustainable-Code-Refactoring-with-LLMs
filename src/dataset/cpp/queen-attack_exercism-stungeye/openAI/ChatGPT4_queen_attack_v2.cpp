#include "queen_attack.h"

#include <stdexcept>
#include <string>
#include <array>

namespace queen_attack {
	chess_board::chess_board(position white, position black) : m_white{white}, m_black{black} {
		if (white == black) throw std::domain_error("Black and white positions cannot be the same.");
	}

	position chess_board::white() const {
		return m_white;
	}

	position chess_board::black() const {
		return m_black;
	}

	bool chess_board::can_attack() const {
		int row_diff = m_white.first - m_black.first;
		int col_diff = m_white.second - m_black.second;
		return row_diff == 0 || col_diff == 0 || std::abs(row_diff) == std::abs(col_diff);
	}

	chess_board::operator std::string() const {
		std::array<std::string, 8> board;
		board.fill("_ _ _ _ _ _ _ _\n");

		board[m_white.first][m_white.second * 2] = 'W';
		board[m_black.first][m_black.second * 2] = 'B';

		std::string result;
		for (const auto& row : board) {
			result += row;
		}
		return result;
	}
}  // namespace queen_attack