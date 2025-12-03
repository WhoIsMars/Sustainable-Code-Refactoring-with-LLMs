#include "hamming.h"
#include <stddef.h>

int compute(const char *lhs, const char *rhs) {
  if (lhs == NULL || rhs == NULL) {
    return -1;
  }

  size_t length = 0;
  const char *l = lhs;
  const char *r = rhs;

  while (*l != '\0' && *r != '\0') {
    l++;
    r++;
    length++;
  }

  if (*l != '\0' || *r != '\0') {
    return -1;
  }

  if (length == 0) {
    return 0;
  }

  int hamming_distance = 0;
  for (size_t i = 0; i < length; ++i) {
    if (lhs[i] != rhs[i]) {
      hamming_distance++;
    }
  }

  return hamming_distance;
}