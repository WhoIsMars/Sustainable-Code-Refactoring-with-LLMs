#ifndef MATCHING_BRACKETS_H
#define MATCHING_BRACKETS_H

#include <stdbool.h>

#define STACK_MAX 256

typedef struct stack_t stack_t;

struct stack_t {
	char c[STACK_MAX];
	int top;
};

void push(char c, stack_t *stack);
int pop(stack_t *stack);
int empty(stack_t stack);
int top(stack_t stack);
bool is_paired(const char *input);

#endif
