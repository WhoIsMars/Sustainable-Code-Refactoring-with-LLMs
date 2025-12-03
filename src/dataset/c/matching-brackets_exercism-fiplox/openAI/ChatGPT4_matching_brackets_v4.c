#include "matching_brackets.h"

void push(char c, stack_t *stack)
{
	if (stack->top < STACK_MAX - 1) {
		stack->c[++stack->top] = c;
	}
}

int pop(stack_t *stack)
{
	return stack->top >= 0 ? stack->c[stack->top--] : 0;
}

int empty(const stack_t *stack)
{
	return stack->top < 0;
}

int top(const stack_t *stack)
{
	return stack->top >= 0 ? stack->c[stack->top] : 0;
}

bool is_paired(const char *input)
{
	stack_t brackets = {.top = -1};

	for (; *input; ++input) {
		char current = *input;
		if (current == '[' || current == '{' || current == '(') {
			push(current, &brackets);
		} else if ((current == ']' && (empty(&brackets) || top(&brackets) != '[')) ||
				   (current == '}' && (empty(&brackets) || top(&brackets) != '{')) ||
				   (current == ')' && (empty(&brackets) || top(&brackets) != '('))) {
			return false;
		} else if (current == ']' || current == '}' || current == ')') {
			pop(&brackets);
		}
	}
	return empty(&brackets);
}