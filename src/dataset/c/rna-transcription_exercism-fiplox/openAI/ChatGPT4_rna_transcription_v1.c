#include "rna_transcription.h"

#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna)
{
	if (!dna) return NULL;

	const char map[256] = {
		['G'] = 'C',
		['C'] = 'G',
		['T'] = 'A',
		['A'] = 'U'
	};

	int len = strlen(dna);
	char *rna = malloc(len + 1);
	if (!rna) return NULL;

	for (int i = 0; i < len; ++i) {
		rna[i] = map[(unsigned char)dna[i]];
	}
	rna[len] = '\0';

	return rna;
}