#include "pangram.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define ALL_LETTERS_PRESENT 0x3FFFFFFU

bool is_pangram(const char *sentence) {
  if (sentence == NULL) {
    return false;
  }

  uint32_t letters_present = 0;
  const char *ptr = sentence;

  while (*ptr != '\0') {
    unsigned char c = *ptr; 
    if (isalpha(c)) {
      letters_present |= 1U << (tolower(c) - 'a');
    }
    ptr++;
  }

  return letters_present == ALL_LETTERS_PRESENT;
}