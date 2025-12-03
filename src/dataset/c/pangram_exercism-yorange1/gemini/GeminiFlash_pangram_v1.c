#include "pangram.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FLAGS_EXCEPT (0x03FFFFFF)

bool is_pangram(const char *sentence) {
  if (sentence == NULL) {
    return false;
  }

  uint32_t flags = 0;
  const char *ptr = sentence;

  while (*ptr != '\0') {
    unsigned char c = *ptr; 
    if (isalpha(c)) {
      flags |= 1 << (tolower(c) - 'a');
    }
    ptr++;
  }

  return flags == FLAGS_EXCEPT;
}