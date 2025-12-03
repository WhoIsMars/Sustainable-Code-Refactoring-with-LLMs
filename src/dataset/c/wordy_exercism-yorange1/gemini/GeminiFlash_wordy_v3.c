#include "wordy.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char get_operation(const char *token) {
  if (!token) {
    return ' ';
  }
  if (token[0] == 'p' && strcmp(token, "plus") == 0) {
    return '+';
  }
  if (token[0] == 'm') {
    if (strcmp(token, "minus") == 0) {
      return '-';
    }
    if (strcmp(token, "multiplied") == 0) {
      return '*';
    }
  }
  if (token[0] == 'd' && strcmp(token, "divided") == 0) {
    return '/';
  }
  return 0;
}

static int calculate(int number1, int number2, char operation) {
  switch (operation) {
  case '+':
    return number1 + number2;
  case '-':
    return number1 - number2;
  case '*':
    return number1 * number2;
  case '/':
    return number1 / number2;
  default:
    return 0;
  }
}

bool answer(const char *question, int *result) {
  if (!question || !result) {
    return false;
  }

  size_t len = strlen(question);
  if (len < 10 || strncmp(question, "What is", 7) != 0) {
    return false;
  }

  const char *start = question + 8;
  const char *end = question + len - 1;
  if (*end != '?') {
    return false;
  }

  int number1;
  if (sscanf(start, "%d", &number1) != 1) {
    return false;
  }

  int answer_val = number1;
  char operation = ' ';
  int number2;
  bool first_op = true;

  start += strspn(start, "0123456789- ");

  while (start < end) {
    char op_char;
    if (first_op) {
      char *op_str = NULL;
      size_t op_len = strcspn(start, " 0123456789");
      op_str = (char *)malloc(op_len + 1);
      if (!op_str) return false;
      strncpy(op_str, start, op_len);
      op_str[op_len] = '\0';
      op_char = get_operation(op_str);
      free(op_str);
      first_op = false;
    } else {
      char *op_str = NULL;
      size_t op_len = strcspn(start, " 0123456789");
      op_str = (char *)malloc(op_len + 1);
      if (!op_str) return false;
      strncpy(op_str, start, op_len);
      op_str[op_len] = '\0';
      if (strcmp(op_str, "by") != 0) {
        free(op_str);
        return false;
      }
      free(op_str);
      start += op_len + strspn(start + op_len, " ");
      op_len = strcspn(start, " 0123456789");
      op_str = (char *)malloc(op_len + 1);
      if (!op_str) return false;
      strncpy(op_str, start, op_len);
      op_str[op_len] = '\0';
      op_char = get_operation(op_str);
      free(op_str);
    }

    if (op_char == 0) {
      return false;
    }
    if (op_char == ' ') {
      *result = answer_val;
      return true;
    }

    start += strspn(start, "abcdefghijklmnopqrstuvwxyz ");

    if (sscanf(start, "%d", &number2) != 1) {
      return false;
    }

    answer_val = calculate(answer_val, number2, op_char);
    start += strspn(start, "0123456789- ");
    first_op = false;
  }

  *result = answer_val;
  return true;
}