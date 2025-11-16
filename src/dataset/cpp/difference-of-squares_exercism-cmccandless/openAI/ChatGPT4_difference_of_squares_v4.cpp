#include "difference_of_squares.h"

namespace squares
{
	int square_of_sum(int n)
	{
		int sum = n * (n + 1) / 2;
		return sum * sum;
	}

	int sum_of_squares(int n)
	{
		return n * (n + 1) * (2 * n + 1) / 6;
	}

	int difference(int n)
	{
		int sum = n * (n + 1) / 2;
		int square_of_sum = sum * sum;
		int sum_of_squares = n * (n + 1) * (2 * n + 1) / 6;
		return square_of_sum - sum_of_squares;
	}
}