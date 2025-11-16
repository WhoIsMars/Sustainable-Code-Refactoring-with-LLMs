#include "queen_attack.h"
#include <stdexcept>
#include <sstream>
#include <array>

namespace queen_attack
{
	chess_board::chess_board(std::pair<int, int> const& white, std::pair<int, int> const& black) : white_{white}, black_{black}
	{
		if (white_ == black_)
		{
			throw std::domain_error("Queens can't occupy the same position!");
		}
	}

	std::pair<int, int> chess_board::white() const
	{
		return white_;
	}

	std::pair<int, int> chess_board::black() const
	{
		return black_;
	}

	chess_board::operator std::string() const
	{
		std::array<std::string, 8> board;
		board.fill("_ _ _ _ _ _ _ _\n");

		board[white_.first][2 * white_.second] = 'W';
		board[black_.first][2 * black_.second] = 'B';

		std::ostringstream buffer;
		for (const auto& line : board)
		{
			buffer << line;
		}
		return buffer.str();
	}

	bool chess_board::can_attack() const
	{
		int row_diff = white_.first - black_.first;
		int col_diff = white_.second - black_.second;

		return row_diff == 0 || col_diff == 0 || std::abs(row_diff) == std::abs(col_diff);
	}
}