#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;
	int i = 0;
	
	// Single pass comparison with early termination on length mismatch
	while (lhs[i] && rhs[i]) {
		if (lhs[i] != rhs[i])
			distance++;
		i++;
	}
	
	// Check if strings have different lengths
	if (lhs[i] || rhs[i])
		return -1;
	
	return distance;
}