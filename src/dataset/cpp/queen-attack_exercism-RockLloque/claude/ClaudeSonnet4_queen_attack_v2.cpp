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
#include <cmath>

namespace queen_attack
{
	chess_board::chess_board(std::pair<int, int> const&  white, std::pair<int, int> const&  black): white_{white}, black_{black}	
	{
		if( white_ == black_)
		{
			throw std::domain_error("Queens can't occupy the same position!");
		}
	}
	
	const std::pair<int, int>& chess_board::white() const
	{
		return white_;
	}
	
	const std::pair<int, int>& chess_board::black() const
	{
		return black_;
	}

	chess_board::operator std::string () const
	{
		std::string result;
		result.reserve(144); // 8 lines * 18 chars per line
		
		for( int i = 0; i < 8; ++i)
		{
			if( i == white_.first && i == black_.first)
			{
				std::string line{"_ _ _ _ _ _ _ _\n"};
				line[2 * white_.second] = 'W';
				line[2 * black_.second] = 'B';
				result += line;
			}
			else if( i == white_.first)
			{
				std::string line{"_ _ _ _ _ _ _ _\n"};
				line[2 * white_.second] = 'W';
				result += line;
			}
			else if( i == black_.first)
			{
				std::string line{"_ _ _ _ _ _ _ _\n"};
				line[2 * black_.second] = 'B';
				result += line;
			}
			else
			{
				result += "_ _ _ _ _ _ _ _\n";
			}
		}
		return result;
	}

	bool chess_board::can_attack() const
	{
		return (white_.first == black_.first) ||
		       (white_.second == black_.second) ||
		       (std::abs(white_.first - black_.first) == std::abs(white_.second - black_.second));
	}
}