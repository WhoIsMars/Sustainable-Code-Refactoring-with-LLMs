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
    if (isalpha((unsigned char)*sentence)) {
      pos = (tolower((unsigned char)*sentence) - 'a');
      used |= (1 << pos);
    }
    sentence++;
  }

  return used == 0x3ffffff;
}