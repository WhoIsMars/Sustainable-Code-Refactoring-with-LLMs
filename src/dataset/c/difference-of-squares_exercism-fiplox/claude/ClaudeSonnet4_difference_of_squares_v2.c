#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number)
{
	return number * (number + 1) * (2 * number + 1) / 6;
}

unsigned int square_of_sum(unsigned int number)
{
	unsigned int sum = number * (number + 1) / 2;
	return sum * sum;
}

unsigned int difference_of_squares(unsigned int number)
{
	unsigned int n = number;
	unsigned int n2 = n * n;
	return n * (n + 1) * (3 * n2 - n - 2) / 12;
}