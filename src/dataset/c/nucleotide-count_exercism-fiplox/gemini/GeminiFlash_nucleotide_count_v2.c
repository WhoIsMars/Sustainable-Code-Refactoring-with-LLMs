#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>

char *count(const char *dna_strand) {
  int a = 0, c = 0, g = 0, t = 0;
  char *res = malloc(64);

  if (!res) {
    return NULL; // Handle memory allocation failure
  }

  while (*dna_strand) {
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
      sprintf(res, "A:%d C:%d G:%d T:%d", a, c, g, t);
      return res;
    }
    dna_strand++;
  }

  sprintf(res, "A:%d C:%d G:%d T:%d", a, c, g, t);
  return res;
}