#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>

char *count(const char *dna_strand)
{
	int counts[4] = {0}; // 0: A, 1: C, 2: G, 3: T
	char *res = malloc(32); // Reduced memory allocation size

	if (!res) return NULL; // Check for malloc failure

	while (*dna_strand) {
		switch (*dna_strand) {
			case 'A': counts[0]++; break;
			case 'C': counts[1]++; break;
			case 'G': counts[2]++; break;
			case 'T': counts[3]++; break;
			default: 
				free(res); // Free allocated memory on invalid input
				return NULL;
		}
		dna_strand++;
	}

	snprintf(res, 32, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);
	return res;
}