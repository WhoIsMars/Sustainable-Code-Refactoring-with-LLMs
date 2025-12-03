#include "isogram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  bool letters[26] = {false};
  const char *p = phrase;

  while (*p) {
    if (isalpha(*p)) {
      int index = tolower(*p) - 'a';
      if (letters[index]) {
        return false;
      }
      letters[index] = true;
    }
    p++;
  }

  return true;
}