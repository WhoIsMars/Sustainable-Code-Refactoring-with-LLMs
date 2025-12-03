#include "isogram.h"

#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  size_t len = 0;
  while (phrase[len] != '\0') {
    len++;
  }

  if (len <= 1) {
    return true;
  }

  bool seen[26] = {false};

  for (size_t i = 0; i < len; i++) {
    unsigned char c = (unsigned char)phrase[i];
    if (isalpha(c)) {
      c = tolower(c);
      size_t index = c - 'a';
      if (seen[index]) {
        return false;
      } else {
        seen[index] = true;
      }
    }
  }

  return true;
}