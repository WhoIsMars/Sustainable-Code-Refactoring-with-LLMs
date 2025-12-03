#include "square_root.h"

unsigned int square_root(unsigned int number)
{
	unsigned int i = 0;

	while (i <= number)
	{
		if(i*i == number)
			return i;
		i++;
	}
	return -1;
}