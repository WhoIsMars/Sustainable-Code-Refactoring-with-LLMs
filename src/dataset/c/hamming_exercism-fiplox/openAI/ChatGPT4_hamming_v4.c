#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;

	for (; *lhs && *rhs; ++lhs, ++rhs) {
		distance += (*lhs != *rhs);
	}

	return (*lhs || *rhs) ? -1 : distance;
}