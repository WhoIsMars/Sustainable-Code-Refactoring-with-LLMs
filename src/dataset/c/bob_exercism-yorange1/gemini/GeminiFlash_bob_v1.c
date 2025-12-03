#include "bob.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *hey_bob(char *greeting) {
  assert(greeting != NULL);

  size_t len = strlen(greeting);
  bool has_alpha = false;
  bool is_upper = true;
  bool is_question = false;
  bool has_non_space = false;

  // Trim trailing whitespace and check for question mark
  size_t i = len;
  while (i > 0 && isspace(greeting[i - 1])) {
    i--;
  }

  if (i > 0 && greeting[i - 1] == '?') {
    is_question = true;
  }

  // Iterate from the beginning to find relevant characteristics
  for (size_t j = 0; j < i; j++) {
    if (!isspace(greeting[j])) {
      has_non_space = true;
    }
    if (isalpha(greeting[j])) {
      has_alpha = true;
      if (islower(greeting[j])) {
        is_upper = false;
      }
    }
  }

  char *answer = NULL;

  if (!has_non_space) {
    if (asprintf(&answer, "Fine. Be that way!") == -1) {
      perror("asprintf");
      exit(EXIT_FAILURE);
    }
  } else if (has_alpha && is_upper && !is_question) {
    if (asprintf(&answer, "Whoa, chill out!") == -1) {
      perror("asprintf");
      exit(EXIT_FAILURE);
    }
  } else if (has_alpha && is_upper && is_question) {
    if (asprintf(&answer, "Calm down, I know what I'm doing!") == -1) {
      perror("asprintf");
      exit(EXIT_FAILURE);
    }
  } else if (is_question) {
    if (asprintf(&answer, "Sure.") == -1) {
      perror("asprintf");
      exit(EXIT_FAILURE);
    }
  } else {
    if (asprintf(&answer, "Whatever.") == -1) {
      perror("asprintf");
      exit(EXIT_FAILURE);
    }
  }

  return answer;
}