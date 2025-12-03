#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>

char *count(const char *dna_strand) {
  int a = 0, c = 0, g = 0, t = 0;
  char *res = malloc(18);

  if (res == NULL) {
    return NULL;
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
        res[0] = '\0';
        return res;
    }
    dna_strand++;
  }

  snprintf(res, 18, "A:%d C:%d G:%d T:%d", a, c, g, t);
  return res;
}