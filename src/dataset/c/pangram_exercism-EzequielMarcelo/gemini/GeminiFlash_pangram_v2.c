#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
  if (sentence == NULL) {
    return false;
  }

  int seen = 0;
  int alphabet_mask = 0;

  while (*sentence) {
    unsigned char c = (unsigned char)tolower(*sentence);
    if (c >= 'a' && c <= 'z') {
      int index = c - 'a';
      int mask = 1 << index;
      if (!(alphabet_mask & mask)) {
        alphabet_mask |= mask;
        seen++;
        if (seen == ALPHABET_COUNT) {
          return true;
        }
      }
    }
    sentence++;
  }

  return seen == ALPHABET_COUNT;
}