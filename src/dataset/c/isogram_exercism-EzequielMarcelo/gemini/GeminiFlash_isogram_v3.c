#include "isogram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  unsigned int seen = 0;

  for (const char *p = phrase; *p != '\0'; ++p) {
    char c = tolower(*p);
    if (c >= 'a' && c <= 'z') {
      int index = c - 'a';
      unsigned int mask = 1u << index;

      if (seen & mask) {
        return false;
      }

      seen |= mask;
    }
  }

  return true;
}