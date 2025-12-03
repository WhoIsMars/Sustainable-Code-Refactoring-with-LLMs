#include "nucleotide_count.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand) {
  int counts[4] = {0};
  char *res = malloc(64);
  if (!res) return NULL;

  while (*dna_strand) {
    switch (*dna_strand) {
      case 'A':
        counts[0]++;
        break;
      case 'C':
        counts[1]++;
        break;
      case 'G':
        counts[2]++;
        break;
      case 'T':
        counts[3]++;
        break;
      default:
        res[0] = '\0';
        return res;
    }
    dna_strand++;
  }

  snprintf(res, 64, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);

  return res;
}