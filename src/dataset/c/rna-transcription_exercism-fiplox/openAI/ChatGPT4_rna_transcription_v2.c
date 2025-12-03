#include "rna_transcription.h"

#include <stdlib.h>

char *to_rna(const char *dna)
{
	if (!dna) return NULL;

	char *rna = malloc(strlen(dna) + 1);
	if (!rna) return NULL;

	char *p = rna;
	while (*dna) {
		switch(*dna++) {
			case 'G': *p++ = 'C'; break;
			case 'C': *p++ = 'G'; break;
			case 'T': *p++ = 'A'; break;
			case 'A': *p++ = 'U'; break;
			default: free(rna); return NULL; // Handle invalid input
		}
	}
	*p = '\0';

	return rna;
}