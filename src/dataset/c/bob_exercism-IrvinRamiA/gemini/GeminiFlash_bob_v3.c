#include "bob.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *hey_bob(char *greeting) {
  bool question = false;
  bool yell = true;
  bool nothing = true;
  bool has_letter = false;
  size_t len = strlen(greeting);
  char *response = (char *)malloc(65 * sizeof(char));

  if (response == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < len; ++i) {
    if (!isspace(greeting[i])) {
      nothing = false;
    }

    if (isupper(greeting[i])) {
      has_letter = true;
    } else if (islower(greeting[i])) {
      yell = false;
      has_letter = true;
    } else {
      yell = false;
    }

    if (greeting[i] == '?') {
      question = true;
    }
  }

  if (nothing) {
    sprintf(response, "Fine. Be that way!");
  } else if (question && yell && has_letter) {
    sprintf(response, "Calm down, I know what I'm doing!");
  } else if (question) {
    sprintf(response, "Sure.");
  } else if (yell && has_letter) {
    sprintf(response, "Whoa, chill out!");
  } else {
    sprintf(response, "Whatever.");
  }

  return response;
}