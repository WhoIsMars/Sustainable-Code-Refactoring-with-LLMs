#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
	int counts[4] = {0}; // Index 0: A, 1: C, 2: G, 3: T
	const char *ptr = dna_strand;

	while (*ptr) {
		switch (*ptr) {
			case 'A':
				counts[0]++;
				break;
			case 'C':
				counts[1]++;
				break;
			case 'G':
				counts[2]++;
				break;
			case 'T':
				counts[3]++;
				break;
			default:
				return NULL; // Invalid character, return NULL
		}
		ptr++;
	}

	// Allocate only the required memory for the result
	size_t res_len = snprintf(NULL, 0, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]) + 1;
	char *res = malloc(res_len);
	if (res) {
		snprintf(res, res_len, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);
	}

	return res;
}