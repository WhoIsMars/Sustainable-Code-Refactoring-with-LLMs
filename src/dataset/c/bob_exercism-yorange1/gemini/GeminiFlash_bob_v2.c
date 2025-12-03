#include "bob.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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

  // Iterate from the end to find the last non-space character and question mark
  for (size_t i = len; i > 0; --i) {
    char c = greeting[i - 1];

    if (!isspace(c)) {
      has_non_space = true;
      if (c == '?') {
        is_question = true;
      }
      break; // Found the last non-space, no need to continue searching for '?'
    }
  }

  // Early exit for empty or whitespace-only strings
  if (!has_non_space) {
    char *answer;
    asprintf(&answer, "Fine. Be that way!");
    return answer;
  }

  // Check for yelling only if there are alphabetic characters
  for (size_t i = 0; i < len; ++i) {
    if (isalpha(greeting[i])) {
      has_alpha = true;
      if (islower(greeting[i])) {
        is_upper = false;
        break; // No need to continue if a lowercase character is found
      }
    }
  }

  char *answer = NULL;

  if (has_alpha && is_upper) {
    if (is_question) {
      asprintf(&answer, "Calm down, I know what I'm doing!");
    } else {
      asprintf(&answer, "Whoa, chill out!");
    }
  } else if (is_question) {
    asprintf(&answer, "Sure.");
  } else {
    asprintf(&answer, "Whatever.");
  }

  return answer;
}