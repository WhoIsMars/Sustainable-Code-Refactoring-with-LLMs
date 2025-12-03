#include "two_fer.h"

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE (100)

void two_fer(char *buffer, const char *name) {
  const char *use_name = (name && *name) ? name : "you";
  snprintf(buffer, BUFFER_SIZE, "One for %s, one for me.", use_name);
}