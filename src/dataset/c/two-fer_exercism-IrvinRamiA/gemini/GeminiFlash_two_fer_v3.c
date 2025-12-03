#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) {
  const char* default_name = "you";
  const char* actual_name = (name == NULL) ? default_name : name;

  size_t name_len = strlen(actual_name);
  size_t base_len = strlen("One for , one for me.");

  // Pre-calculate the required buffer size to avoid potential buffer overflows.
  size_t required_size = strlen("One for ") + name_len + strlen(", one for me.") + 1;

  // Check if the provided buffer is large enough.  If not, truncate.  This is safer than overflowing.
  size_t buffer_size = 0;
  char* temp = buffer;
  while (*temp++) buffer_size++;

  if (required_size > buffer_size) {
      required_size = buffer_size;
  }

  strcpy(buffer, "One for ");
  strncat(buffer, actual_name, required_size - strlen(buffer) - strlen(", one for me.") - 1);
  strcat(buffer, ", one for me.");

  // Ensure null termination, especially after potential truncation.
  buffer[required_size -1] = '\0';
}