#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;

	while (*lhs && *rhs) {
		if (*lhs++ != *rhs++)
			distance++;
	}

	return (*lhs || *rhs) ? -1 : distance;
}