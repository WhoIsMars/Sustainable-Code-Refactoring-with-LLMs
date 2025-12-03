#include "rna_transcription.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *to_rna(const char *dna)
{
	int len = strlen(dna);
	char *rna = malloc(len + 1);

	if (rna == NULL) {
		return NULL; // Handle memory allocation failure
	}

	for (int i = 0; i < len; ++i) {
		switch (dna[i]) {
			case 'G':
				rna[i] = 'C';
				break;
			case 'C':
				rna[i] = 'G';
				break;
			case 'T':
				rna[i] = 'A';
				break;
			case 'A':
				rna[i] = 'U';
				break;
			default:
				free(rna);
				return NULL; // Handle invalid input
		}
	}
	rna[len] = '\0';

	return rna;
}