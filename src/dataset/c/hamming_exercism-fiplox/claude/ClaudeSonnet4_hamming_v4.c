#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;
	const char *p1 = lhs;
	const char *p2 = rhs;
	
	while (*p1 && *p2) {
		if (*p1 != *p2)
			distance++;
		p1++;
		p2++;
	}
	
	if (*p1 || *p2)
		return -1;
	
	return distance;
}