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
#include <string>
#include <cmath>

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
		std::string result;
		result.reserve(144);
		
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				if(i == white_.first && j == white_.second)
				{
					result += 'W';
				}
				else if(i == black_.first && j == black_.second)
				{
					result += 'B';
				}
				else
				{
					result += '_';
				}
				
				if(j < 7) result += ' ';
			}
			result += '\n';
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