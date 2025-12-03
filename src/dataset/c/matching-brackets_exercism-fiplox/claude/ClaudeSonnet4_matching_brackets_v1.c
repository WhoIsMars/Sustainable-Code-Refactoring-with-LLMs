#include "matching_brackets.h"

static inline void push(char c, stack_t *stack)
{
	if (stack->top >= STACK_MAX)
		return;
	stack->c[++stack->top] = c;
}

static inline char pop(stack_t *stack)
{
	return stack->c[stack->top--];
}

static inline int empty(stack_t stack)
{
	return stack.top < 0;
}

static inline char top(stack_t stack)
{
	return stack.c[stack.top];
}

bool is_paired(const char *input)
{
	stack_t brackets;
	brackets.top = -1;
	
	const char *p = input;
	char c, expected;
	
	while ((c = *p++)) {
		switch (c) {
			case '[':
			case '{':
			case '(':
				push(c, &brackets);
				break;
			case ']':
				expected = '[';
				goto check_match;
			case '}':
				expected = '{';
				goto check_match;
			case ')':
				expected = '(';
			check_match:
				if (empty(brackets) || top(brackets) != expected)
					return false;
				pop(&brackets);
				break;
		}
	}
	return empty(brackets);
}