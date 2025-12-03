#include "matching_brackets.h"

bool is_paired(const char *input)
{
	char stack[STACK_MAX];
	int top = -1;

	while (*input) {
		char c = *input++;
		
		if (c == '[' || c == '{' || c == '(') {
			if (top >= STACK_MAX - 1)
				return false;
			stack[++top] = c;
		} else if (c == ']' || c == '}' || c == ')') {
			if (top < 0)
				return false;
			
			char expected = (c == ']') ? '[' : (c == '}') ? '{' : '(';
			if (stack[top--] != expected)
				return false;
		}
	}
	
	return top < 0;
}