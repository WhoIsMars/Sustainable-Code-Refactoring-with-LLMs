#include "matching_brackets.h"

void push(char c, stack_t *stack)
{
	if (stack->top >= STACK_MAX)
		return;
	stack->top++;
	stack->c[stack->top] = c;
}

int pop(stack_t *stack)
{
	return stack->c[stack->top--];
}

int empty(stack_t stack)
{
	return stack.top < 0;
}

int top(stack_t stack)
{
	return stack.c[stack.top];
}

bool is_paired(const char *input)
{
	stack_t brackets;
	brackets.top = -1;

	while (*input) {
		switch (*input) {
			case '[':
			case '{':
			case '(':
				push(*input, &brackets);
				break;
			case ']':
				if (empty(brackets) || top(brackets) != '[')
					return 0;
				pop(&brackets);
				break;
			case '}':
				if (empty(brackets) || top(brackets) != '{')
					return 0;
				pop(&brackets);
				break;
			case ')':
				if (empty(brackets) || top(brackets) != '(')
					return 0;
				pop(&brackets);
				break;
		}
		input++;
	}
	return empty(brackets);
}
