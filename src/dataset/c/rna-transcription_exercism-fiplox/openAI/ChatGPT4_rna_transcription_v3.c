#include "rna_transcription.h"

#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna)
{
	if (!dna) return NULL;

	int len = strlen(dna);
	char *rna = malloc(len + 1);
	if (!rna) return NULL;

	for (int i = 0; i < len; ++i) {
		char nucleotide = dna[i];
		if (nucleotide == 'G') rna[i] = 'C';
		else if (nucleotide == 'C') rna[i] = 'G';
		else if (nucleotide == 'T') rna[i] = 'A';
		else if (nucleotide == 'A') rna[i] = 'U';
		else {
			free(rna);
			return NULL;
		}
	}
	rna[len] = '\0';

	return rna;
}