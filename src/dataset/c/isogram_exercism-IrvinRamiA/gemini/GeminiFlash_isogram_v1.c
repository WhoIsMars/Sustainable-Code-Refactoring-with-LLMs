#include "isogram.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  size_t length = strlen(phrase);
  if (length <= 1) {
    return true;
  }

  bool letters[26] = {false}; // Assuming only ASCII letters

  for (size_t i = 0; i < length; i++) {
    char c = tolower(phrase[i]);
    if (isalpha(c)) {
      int index = c - 'a';
      if (letters[index]) {
        return false;
      }
      letters[index] = true;
    }
  }

  return true;
}