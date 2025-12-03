#include "matching_brackets.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool is_paired(const char *input) {
  if (input == NULL || *input == '\0') {
    return true;
  }

  size_t length = strlen(input);
  char stack[length];
  size_t sp = 0;

  for (size_t i = 0; i < length; ++i) {
    char c = input[i];
    switch (c) {
    case '(':
    case '[':
    case '{':
      stack[sp++] = c;
      break;
    case ')':
      if (sp == 0 || stack[--sp] != '(') {
        return false;
      }
      break;
    case ']':
      if (sp == 0 || stack[--sp] != '[') {
        return false;
      }
      break;
    case '}':
      if (sp == 0 || stack[--sp] != '{') {
        return false;
      }
      break;
    default:
      // Ignore other characters
      break;
    }
  }

  return sp == 0;
}