#include "hamming.h"
#include <stddef.h>

int compute(const char *lhs, const char *rhs) {
  if (!lhs || !rhs) {
    return -1;
  }

  size_t len = 0;
  while (lhs[len] && rhs[len]) {
    len++;
  }

  if (lhs[len] || rhs[len]) {
    return -1;
  }

  int h = 0;
  for (size_t i = 0; i < len; ++i) {
    if (lhs[i] != rhs[i]) {
      h++;
    }
  }

  return h;
}