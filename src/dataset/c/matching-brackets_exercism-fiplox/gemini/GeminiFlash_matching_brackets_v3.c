#include "matching_brackets.h"

void push(char c, stack_t *stack) {
  if (stack->top >= STACK_MAX - 1) return;
  stack->c[++stack->top] = c;
}

int pop(stack_t *stack) { return stack->c[stack->top--]; }

int empty(const stack_t *stack) { return stack->top < 0; }

int top(const stack_t *stack) { return stack->c[stack->top]; }

bool is_paired(const char *input) {
  stack_t brackets;
  brackets.top = -1;

  while (*input) {
    char current_char = *input;
    switch (current_char) {
      case '[':
      case '{':
      case '(':
        push(current_char, &brackets);
        break;
      case ']':
        if (empty(&brackets) || top(&brackets) != '[') return false;
        pop(&brackets);
        break;
      case '}':
        if (empty(&brackets) || top(&brackets) != '{') return false;
        pop(&brackets);
        break;
      case ')':
        if (empty(&brackets) || top(&brackets) != '(') return false;
        pop(&brackets);
        break;
      default:
        break;
    }
    input++;
  }
  return empty(&brackets);
}