#include "hamming.h"
#include <string.h>

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;
	int len_lhs = strlen(lhs);
	int len_rhs = strlen(rhs);
	if (len_lhs != len_rhs)
		return -1;

	for (int i = 0; i < len_lhs; ++i) {
		if (lhs[i] != rhs[i])
			distance++;
	}

	return distance;
}
