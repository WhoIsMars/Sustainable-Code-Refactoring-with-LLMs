#include "bob.h"

#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define WITHOUT_ANYTHING (0x00)
#define ANYTHING_ELSE (0x01)
#define YELL (0x02)
#define QUESTION (0x04)

char *hey_bob(char *greeting) {
  assert(NULL != greeting);

  uint8_t flag = WITHOUT_ANYTHING;
  size_t len = strlen(greeting);

  bool has_alpha = false;
  bool all_upper = true;
  bool has_anything = false;
  bool is_question = false;

  if (len == 0) {
    asprintf(&greeting, "Fine. Be that way!");
    return greeting;
  }

  for (size_t i = len - 1; i > 0 && isspace(greeting[i]); --i) {
    greeting[i] = '\0';
    len--;
  }

  if (greeting[len - 1] == '?') {
    is_question = true;
  }

  for (size_t i = 0; i < len; i++) {
    if (!isspace(greeting[i])) {
      has_anything = true;
      if (isalpha(greeting[i])) {
        has_alpha = true;
        if (islower(greeting[i])) {
          all_upper = false;
        }
      }
    }
  }

  if (!has_anything) {
    asprintf(&greeting, "Fine. Be that way!");
    return greeting;
  }

  if (has_alpha && all_upper) {
    flag |= YELL;
  }

  if (is_question) {
    flag |= QUESTION;
  }

  char *answer = NULL;

  switch (flag) {
  case WITHOUT_ANYTHING:
    asprintf(&answer, "Fine. Be that way!");
    break;
  case ANYTHING_ELSE:
    asprintf(&answer, "Whatever.");
    break;
  case QUESTION:
    asprintf(&answer, "Sure.");
    break;
  case YELL:
    asprintf(&answer, "Whoa, chill out!");
    break;
  case YELL | QUESTION:
    asprintf(&answer, "Calm down, I know what I'm doing!");
    break;
  default:
    asprintf(&answer, "Whatever.");
    break;
  }

  return answer;
}