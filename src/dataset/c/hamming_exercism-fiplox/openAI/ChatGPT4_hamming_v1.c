#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
	int distance = 0;

	for (int i = 0; lhs[i] != '\0' && rhs[i] != '\0'; ++i) {
		if (lhs[i] != rhs[i])
			distance++;
	}

	return (lhs[0] == '\0' || rhs[0] == '\0' || lhs[strlen(lhs)] != '\0' || rhs[strlen(rhs)] != '\0') ? -1 : distance;
}