#include "isogram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL) {
    return false;
  }

  bool seen[26] = {false};
  for (int i = 0; phrase[i] != '\0'; ++i) {
    if (isalpha(phrase[i])) {
      int index = tolower(phrase[i]) - 'a';
      if (seen[index]) {
        return false;
      }
      seen[index] = true;
    }
  }
  return true;
}