#include "isogram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL || *phrase == '\0') {
    return true;
  }

  bool seen[26] = {false};
  const char *p = phrase;

  while (*p) {
    unsigned char c = (unsigned char)*p;
    if (isalpha(c)) {
      c = tolower(c);
      unsigned char index = c - 'a';
      if (seen[index]) {
        return false;
      }
      seen[index] = true;
    }
    ++p;
  }

  return true;
}