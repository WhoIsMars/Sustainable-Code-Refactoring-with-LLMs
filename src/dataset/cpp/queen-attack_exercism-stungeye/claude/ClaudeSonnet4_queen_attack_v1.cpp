#include "queen_attack.h"

#include <stdexcept>

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
		const int row_diff = m_white.first - m_black.first;
		const int col_diff = m_white.second - m_black.second;
		
		return row_diff == 0 
			   || col_diff == 0
			   || (row_diff * row_diff) == (col_diff * col_diff);
	}

	chess_board::operator std::string() const {
		std::string board(144, '_');
		
		// Set up row structure
		for (int i = 1; i < 144; i += 2) {
			if ((i + 1) % 18 == 0) {
				board[i] = '\n';
			} else {
				board[i] = ' ';
			}
		}
		
		board[m_white.first * 18 + m_white.second * 2] = 'W';
		board[m_black.first * 18 + m_black.second * 2] = 'B';

		return board;
	}
}  // namespace queen_attack