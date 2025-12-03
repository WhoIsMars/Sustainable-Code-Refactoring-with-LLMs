#include "hamming.h"
#include <stddef.h>

int compute(const char *lhs, const char *rhs) {
  if (lhs == NULL || rhs == NULL) {
    return -1;
  }

  size_t length = 0;
  while (lhs[length] != '\0' && rhs[length] != '\0') {
    length++;
  }

  if (lhs[length] != '\0' || rhs[length] != '\0') {
    return -1;
  }

  int hamming_distance = 0;
  for (size_t i = 0; i < length; i++) {
    if (lhs[i] != rhs[i]) {
      hamming_distance++;
    }
  }

  return hamming_distance;
}