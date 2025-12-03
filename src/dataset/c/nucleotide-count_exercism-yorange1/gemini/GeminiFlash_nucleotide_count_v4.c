#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE (50)

char *count(const char *dna_strand) {
  if (dna_strand == NULL) {
    return NULL;
  }

  size_t length = strlen(dna_strand);
  int counts[4] = {0};
  bool invalid_nucleotide = false;

  for (size_t i = 0; i < length; ++i) {
    switch (dna_strand[i]) {
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
        invalid_nucleotide = true;
        break;
    }
    if (invalid_nucleotide) break;
  }

  char *result = (char *)malloc(BUFFER_SIZE);
  if (result == NULL) {
    return NULL;
  }

  if (invalid_nucleotide) {
    result[0] = '\0';
  } else {
    snprintf(result, BUFFER_SIZE, "A:%d C:%d G:%d T:%d", counts[0], counts[1],
             counts[2], counts[3]);
  }

  return result;
}