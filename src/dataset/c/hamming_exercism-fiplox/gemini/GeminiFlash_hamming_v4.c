#include "hamming.h"
#include <string.h>
#include <stddef.h>

int compute(const char *lhs, const char *rhs)
{
  size_t len_lhs;
  size_t len_rhs;

  len_lhs = strlen(lhs);
  len_rhs = strlen(rhs);

  if (len_lhs != len_rhs) {
    return -1;
  }

  int distance = 0;
  for (size_t i = 0; i < len_lhs; ++i) {
    distance += (lhs[i] != rhs[i]);
  }

  return distance;
}