#include "difference_of_squares.h"
#include <math.h>

unsigned int sum_of_squares(unsigned int number)
{
	unsigned int i = 0;
	unsigned int t = 0;
	while (i <= number)
	{
		t += pow(i,2);
		i++;
	}
	return (t);
}

unsigned int square_of_sum(unsigned int number)
{
	unsigned int i = 0;
	unsigned int t = 0;
	while (i <= number)
	{
		t += i;
		i++;
	}
	return (pow(t,2));
}

unsigned int difference_of_squares(unsigned int number)
{
	return (square_of_sum(number) - sum_of_squares(number));
}