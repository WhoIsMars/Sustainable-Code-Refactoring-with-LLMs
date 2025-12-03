#include "matching_brackets.h"

void push(char c, stack_t *stack)
{
	stack->c[++stack->top] = c;
}

void pop(stack_t *stack)
{
	stack->top--;
}

bool empty(const stack_t *stack)
{
	return stack->top < 0;
}

char top(const stack_t *stack)
{
	return stack->c[stack->top];
}

bool is_paired(const char *input)
{
	stack_t brackets = {.top = -1};

	for (; *input; input++) {
		switch (*input) {
			case '[': case '{': case '(':
				if (brackets.top < STACK_MAX - 1) 
					push(*input, &brackets);
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
		}
	}
	return empty(&brackets);
}