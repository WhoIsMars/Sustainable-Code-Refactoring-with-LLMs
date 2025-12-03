#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
  if (sentence == NULL) {
    return false;
  }

  int seen = 0;
  int count = 0;

  while (*sentence) {
    unsigned char c = (unsigned char)tolower(*sentence);
    if (c >= 'a' && c <= 'z') {
      int index = c - 'a';
      if (!(seen & (1 << index))) {
        seen |= (1 << index);
        count++;
        if (count == ALPHABET_COUNT) {
          return true;
        }
      }
    }
    sentence++;
  }

  return false;
}