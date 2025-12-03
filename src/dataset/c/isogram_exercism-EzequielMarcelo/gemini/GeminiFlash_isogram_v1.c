#include "isogram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  bool seen[26] = {false};
  const char *p = phrase;

  while (*p) {
    if (isalpha(*p)) {
      int index = tolower(*p) - 'a';
      if (seen[index]) {
        return false;
      }
      seen[index] = true;
    }
    p++;
  }

  return true;
}