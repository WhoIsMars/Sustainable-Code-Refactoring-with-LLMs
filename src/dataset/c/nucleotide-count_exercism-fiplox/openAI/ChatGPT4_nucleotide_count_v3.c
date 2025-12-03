#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
	int counts[4] = {0}; // A, C, G, T
	const char *valid_chars = "ACGT";

	for (; *dna_strand; dna_strand++) {
		char *pos = strchr(valid_chars, *dna_strand);
		if (!pos) return NULL; // Invalid character
		counts[pos - valid_chars]++;
	}

	char *res = malloc(32);
	if (!res) return NULL; // Handle memory allocation failure
	snprintf(res, 32, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);

	return res;
}