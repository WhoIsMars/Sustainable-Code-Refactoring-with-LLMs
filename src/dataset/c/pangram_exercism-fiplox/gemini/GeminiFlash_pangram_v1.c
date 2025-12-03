#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
  if (!sentence || !*sentence) {
    return false;
  }

  unsigned int used = 0;
  int pos;

  while (*sentence) {
    if (isalpha(*sentence)) {
      pos = tolower(*sentence) - 'a';
      if (pos >= 0 && pos < 26) {
        used |= (1 << pos);
      }
    }
    sentence++;
  }

  return used == ((1 << 26) - 1);
}