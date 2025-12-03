#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence) {
  if (!sentence || !*sentence) {
    return false;
  }

  unsigned int used = 0;
  const char *s = sentence;

  while (*s) {
    unsigned char c = (unsigned char)*s;
    if (isalpha(c)) {
      unsigned char lower_c = tolower(c);
      unsigned int index = lower_c - 'a';
      used |= (1 << index);
    }
    s++;
  }

  return used == 0x3ffffff;
}