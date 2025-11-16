/*
 * =====================================================================================
 *
 *       Filename:  queen_attack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13.01.2016 13:36:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */

#include "queen_attack.h"
#include <stdexcept>
#include <array>

namespace queen_attack
{
	chess_board::chess_board(std::pair<int, int> const& white, std::pair<int, int> const& black): white_{white}, black_{black}	
	{
		if(white_ == black_)
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

	chess_board::operator std::string () const
	{
		std::array<char, 144> board;
		constexpr const char* line_template = "_ _ _ _ _ _ _ _\n";
		
		for(int i = 0; i < 8; ++i)
		{
			char* line_start = board.data() + i * 18;
			std::memcpy(line_start, line_template, 18);
			
			if(i == white_.first)
			{
				line_start[2 * white_.second] = 'W';
			}
			if(i == black_.first)
			{
				line_start[2 * black_.second] = 'B';
			}
		}
		
		return std::string(board.data(), 144);
	}

	bool chess_board::can_attack() const
	{
		return (white_.first == black_.first) ||
		       (white_.second == black_.second) ||
		       (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second));
	}
}