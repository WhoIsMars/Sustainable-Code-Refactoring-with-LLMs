#include "binary.h"
#include <stddef.h>

int convert(const char *input) {
  int result = 0;
  if (input == NULL) return INVALID;

  for (const char *p = input; *p != '\0'; ++p) {
    if (*p == '0') {
      result <<= 1;
    } else if (*p == '1') {
      result = (result << 1) | 1;
    } else {
      return INVALID;
    }
  }
  return result;
}