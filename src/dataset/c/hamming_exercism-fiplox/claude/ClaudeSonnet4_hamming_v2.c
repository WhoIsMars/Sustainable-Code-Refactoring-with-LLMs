#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;
	int i = 0;
	
	while (lhs[i] && rhs[i]) {
		if (lhs[i] != rhs[i])
			distance++;
		i++;
	}
	
	if (lhs[i] || rhs[i])
		return -1;

	return distance;
}