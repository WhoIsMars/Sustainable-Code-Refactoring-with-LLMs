#include "pangram.h"
#include <stdbool.h>
#include <ctype.h>

bool is_pangram(const char *sentence) {
  if (sentence == NULL) {
    return false;
  }

  bool alphabet_present[26] = {false};
  int letters_found = 0;

  for (const char *ptr = sentence; *ptr != '\0' && letters_found < 26; ++ptr) {
    unsigned char c = *ptr;
    if (isalpha(c)) {
      c = tolower(c);
      int index = c - 'a';
      if (!alphabet_present[index]) {
        alphabet_present[index] = true;
        letters_found++;
      }
    }
  }

  return letters_found == 26;
}