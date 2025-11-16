#include "queen_attack.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

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
		
		return row_diff == 0 || col_diff == 0 || std::abs(row_diff) == std::abs(col_diff);
	}

	chess_board::operator std::string() const {
		std::string board;
		board.reserve(144);
		
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (row == m_white.first && col == m_white.second) {
					board += 'W';
				} else if (row == m_black.first && col == m_black.second) {
					board += 'B';
				} else {
					board += '_';
				}
				
				if (col < 7) board += ' ';
			}
			if (row < 7) board += '\n';
		}
		
		return board;
	}
}  // namespace queen_attack