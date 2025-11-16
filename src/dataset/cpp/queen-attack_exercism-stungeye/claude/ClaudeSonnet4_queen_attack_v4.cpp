#include "queen_attack.h"

#include <stdexcept>
#include <cstdlib>

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
		return m_white.first == m_black.first
			   || m_white.second == m_black.second
			   || std::abs(m_white.first - m_black.first)
		            == std::abs(m_white.second - m_black.second);
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
			board += '\n';
		}
		
		return board;
	}
}