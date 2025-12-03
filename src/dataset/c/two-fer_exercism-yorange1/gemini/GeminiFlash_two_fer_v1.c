#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) {
  const char *name_ptr = (name == NULL) ? "you" : name;
  snprintf(buffer, 100, "One for %s, one for me.", name_ptr);
}