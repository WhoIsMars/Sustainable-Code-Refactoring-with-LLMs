#include "queen_attack.h"

#include <stdexcept>
#include <string>

namespace queen_attack {
	chess_board::chess_board(position white, position black) : m_white{white}, m_black{black} {
		if (white == black) throw std::domain_error("Black and white positions cannot be the same.");
	}

	position chess_board::white() const noexcept {
		return m_white;
	}

	position chess_board::black() const noexcept {
		return m_black;
	}

	bool chess_board::can_attack() const noexcept {
		const auto [white_row, white_col] = m_white;
		const auto [black_row, black_col] = m_black;
		return white_row == black_row
			   || white_col == black_col
			   || std::abs(white_row - black_row) == std::abs(white_col - black_col);
	}

	chess_board::operator std::string() const {
		std::string board(127, '_');
		for (int i = 15; i < 127; i += 16) board[i] = '\n';

		board[m_white.first * 16 + m_white.second * 2] = 'W';
		board[m_black.first * 16 + m_black.second * 2] = 'B';

		return board;
	}
}  // namespace queen_attack