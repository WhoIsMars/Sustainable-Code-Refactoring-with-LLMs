#include "difference_of_squares.h"

namespace squares
{
	int square_of_sum(int n)
	{
		int sum = n * (n + 1) / 2; // Using the formula for the sum of the first n natural numbers
		return sum * sum;
	}

	int sum_of_squares(int n)
	{
		// Using the formula for the sum of the squares of the first n natural numbers
		return n * (n + 1) * (2 * n + 1) / 6;
	}

	int difference(int n)
	{
		return square_of_sum(n) - sum_of_squares(n);
	}
}