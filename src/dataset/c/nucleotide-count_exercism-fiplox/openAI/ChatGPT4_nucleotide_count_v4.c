#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
	int counts[4] = {0}; // A, C, G, T
	const char *ptr = dna_strand;

	while (*ptr) {
		switch (*ptr) {
			case 'A': counts[0]++; break;
			case 'C': counts[1]++; break;
			case 'G': counts[2]++; break;
			case 'T': counts[3]++; break;
			default: return NULL;
		}
		ptr++;
	}

	char *res = malloc(32);
	if (!res) return NULL;

	snprintf(res, 32, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);
	return res;
}