#include "hamming.h"

#include <stddef.h>

int compute(const char *lhs, const char *rhs) {
  if (lhs == NULL || rhs == NULL) {
    return -1;
  }

  const char *l = lhs;
  const char *r = rhs;

  // Early exit if strings are different lengths
  while (*l != '\0' && *r != '\0') {
    l++;
    r++;
  }

  if (*l != '\0' || *r != '\0') {
    return -1;
  }

  int ham_dist = 0;
  l = lhs;
  r = rhs;

  while (*l != '\0') {
    if (*l != *r) {
      ham_dist++;
    }
    l++;
    r++;
  }

  return ham_dist;
}