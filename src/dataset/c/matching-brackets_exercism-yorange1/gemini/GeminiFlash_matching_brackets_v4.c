#include "matching_brackets.h"

#include <stdbool.h>
#include <stddef.h>

bool is_paired(const char *input) {
  if (input == NULL || *input == '\0') {
    return true;
  }

  size_t stack_size = 0;
  const char *p = input;
  char stack[1024]; // Assuming a reasonable maximum nesting depth

  while (*p != '\0') {
    char c = *p++;
    switch (c) {
    case '(':
    case '[':
    case '{':
      if (stack_size >= sizeof(stack)) {
        return false; // Stack overflow
      }
      stack[stack_size++] = c;
      break;
    case ')':
      if (stack_size == 0 || stack[--stack_size] != '(') {
        return false;
      }
      break;
    case ']':
      if (stack_size == 0 || stack[--stack_size] != '[') {
        return false;
      }
      break;
    case '}':
      if (stack_size == 0 || stack[--stack_size] != '{') {
        return false;
      }
      break;
    default:
      // Ignore other characters
      break;
    }
  }

  return stack_size == 0;
}