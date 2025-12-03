#include "matching_brackets.h"

void push(char c, stack_t *stack)
{
	if (stack->top >= STACK_MAX)
		return;
	stack->c[++stack->top] = c;
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
	
	const char *ptr = input;
	char current, expected;
	
	while ((current = *ptr++)) {
		if (current == '[' || current == '{' || current == '(') {
			push(current, &brackets);
		} else if (current == ']' || current == '}' || current == ')') {
			if (empty(brackets))
				return 0;
			
			expected = (current == ']') ? '[' : 
					   (current == '}') ? '{' : '(';
			
			if (top(brackets) != expected)
				return 0;
			
			pop(&brackets);
		}
	}
	
	return empty(brackets);
}