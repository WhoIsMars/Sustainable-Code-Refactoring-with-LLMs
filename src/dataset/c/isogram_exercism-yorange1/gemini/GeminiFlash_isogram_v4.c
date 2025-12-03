#include "isogram.h"

#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  const char *p = phrase;
  unsigned int seen = 0;

  while (*p) {
    if (isalpha(*p)) {
      int index = tolower(*p) - 'a';
      if (seen & (1 << index)) {
        return false;
      }
      seen |= (1 << index);
    }
    p++;
  }

  return true;
}