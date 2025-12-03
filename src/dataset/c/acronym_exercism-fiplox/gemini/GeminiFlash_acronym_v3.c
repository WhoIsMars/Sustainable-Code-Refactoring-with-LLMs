#include "acronym.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  if (!phrase || !*phrase) {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *abrev = malloc(phrase_len / 2 + 2); // Allocate conservatively
  if (!abrev) {
    return NULL; // Handle allocation failure
  }

  char *tmp = abrev;
  *tmp++ = toupper(*phrase);

  for (size_t i = 1; i < phrase_len; ++i) {
    if (phrase[i] == ' ' || phrase[i] == '-') {
      // Skip non-alphabetic characters after space or hyphen
      while (i < phrase_len && !isalpha(phrase[i])) {
        i++;
      }

      if (i < phrase_len) {
        *tmp++ = toupper(phrase[i]);
      }
    }
  }

  *tmp = '\0';
  return abrev;
}