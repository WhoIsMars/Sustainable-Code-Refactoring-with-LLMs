#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) {
  const char *actual_name = (name != NULL) ? name : "you";
  size_t name_len = strlen(actual_name);
  const char prefix[] = "One for ";
  const char suffix[] = ", one for me.";
  size_t prefix_len = sizeof(prefix) - 1;
  size_t suffix_len = sizeof(suffix) - 1;
  size_t total_len = prefix_len + name_len + suffix_len;

  if (total_len >= 100) {
    strncpy(buffer, "One for , one for me.", 99);
    buffer[99] = '\0';
    return;
  }

  memcpy(buffer, prefix, prefix_len);
  memcpy(buffer + prefix_len, actual_name, name_len);
  memcpy(buffer + prefix_len + name_len, suffix, suffix_len);
  buffer[total_len] = '\0';
}