#include "queen_attack.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

namespace queen_attack {
	chess_board::chess_board(position white, position black) : m_white{white}, m_black{black} {
		if (white == black) {
			throw std::domain_error("Black and white positions cannot be the same.");
		}
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
		std::string board;
		board.reserve(144); // Pre-allocate memory for the entire board string

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (m_white.first == i && m_white.second == j) {
					board += 'W';
				} else if (m_black.first == i && m_black.second == j) {
					board += 'B';
				} else {
					board += '_';
				}
				if (j < 7) {
					board += ' ';
				}
			}
			board += '\n';
		}

		return board;
	}
}  // namespace queen_attack