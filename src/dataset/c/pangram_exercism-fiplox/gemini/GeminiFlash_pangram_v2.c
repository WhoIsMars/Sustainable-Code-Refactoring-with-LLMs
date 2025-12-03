#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
  if (!sentence) {
    return false;
  }

  bool used[26] = {false};
  int count = 0;

  for (const char *s = sentence; *s != '\0' && count < 26; ++s) {
    if (isalpha(*s)) {
      int index = tolower(*s) - 'a';
      if (!used[index]) {
        used[index] = true;
        count++;
      }
    }
  }

  return count == 26;
}