#include "matching_brackets.h"
#include <stdbool.h>

void push(char c, stack_t *stack) {
  if (stack->top < STACK_MAX - 1) {
    stack->c[++stack->top] = c;
  }
}

int pop(stack_t *stack) {
  if (stack->top >= 0) {
    return stack->c[stack->top--];
  }
  return -1; // Or some other error value indicating stack underflow
}

bool empty(const stack_t *stack) { return stack->top < 0; }

int top(const stack_t *stack) {
  if (stack->top >= 0) {
    return stack->c[stack->top];
  }
  return -1; // Or some other error value indicating stack is empty
}

bool is_paired(const char *input) {
  stack_t brackets;
  brackets.top = -1;

  while (*input) {
    char c = *input;
    switch (c) {
    case '[':
    case '{':
    case '(':
      push(c, &brackets);
      break;
    case ']':
      if (empty(&brackets) || top(&brackets) != '[')
        return false;
      pop(&brackets);
      break;
    case '}':
      if (empty(&brackets) || top(&brackets) != '{')
        return false;
      pop(&brackets);
      break;
    case ')':
      if (empty(&brackets) || top(&brackets) != '(')
        return false;
      pop(&brackets);
      break;
    default:
      // Ignore non-bracket characters.  This avoids unnecessary stack
      // operations and makes the function more robust.
      break;
    }
    input++;
  }
  return empty(&brackets);
}