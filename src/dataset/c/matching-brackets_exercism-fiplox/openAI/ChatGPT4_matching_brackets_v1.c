#include "matching_brackets.h"

void push(char c, stack_t *stack)
{
	stack->c[++stack->top] = c;
}

int pop(stack_t *stack)
{
	return stack->c[stack->top--];
}

int empty(stack_t stack)
{
	return stack.top == -1;
}

int top(stack_t stack)
{
	return stack.c[stack.top];
}

bool is_paired(const char *input)
{
	stack_t brackets = { .top = -1 };

	for (; *input; input++) {
		char current = *input;
		if (current == '[' || current == '{' || current == '(') {
			push(current, &brackets);
		} else if (current == ']' || current == '}' || current == ')') {
			if (empty(brackets)) return false;
			char expected = (current == ']') ? '[' : (current == '}') ? '{' : '(';
			if (top(brackets) != expected) return false;
			pop(&brackets);
		}
	}
	return empty(brackets);
}