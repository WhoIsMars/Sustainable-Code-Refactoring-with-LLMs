#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>

char *count(const char *dna_strand)
{
	int a, c, g ,t;
	char *res = malloc(64);

	*res = '\0';
	a = c = g = t = 0;
	
	while(*dna_strand) {
		switch (*dna_strand) {
			case 'A':
				a++;				
				break;
			case 'C':
				c++;
				break;
			case 'G':
				g++;
				break;
			case 'T':
				t++;
				break;
			default:
				return res;
		}
		dna_strand++;
	}
	sprintf(res, "A:%d C:%d G:%d T:%d", a, c, g, t);

	return res;
}
