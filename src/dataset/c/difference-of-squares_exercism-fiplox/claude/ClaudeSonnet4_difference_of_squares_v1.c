#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number)
{
	return number * (number + 1) * (2 * number + 1) / 6;
}

unsigned int square_of_sum(unsigned int number)
{
	unsigned int sum = number * (number + 1) >> 1;
	return sum * sum;
}

unsigned int difference_of_squares(unsigned int number)
{
	unsigned int n2 = number * number;
	unsigned int n3 = n2 * number;
	return (3 * n2 * (number + 1) - number * (2 * number + 1)) / 12;
}