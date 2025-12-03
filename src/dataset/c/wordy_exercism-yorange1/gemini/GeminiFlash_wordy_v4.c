#include "wordy.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return 0; // Indicate error, caller must check
  }
}

bool answer(const char *question, int *result) {
  if (question == NULL || result == NULL) {
    return false;
  }

  size_t length = strlen(question);
  if (length < 10 || strncmp(question, "What is", 7) != 0) {
    return false;
  }

  const char *ptr = question + 8;
  int number1;
  int num_read = 0;

  if (sscanf(ptr, "%d%n", &number1, &num_read) != 1) {
    return false;
  }
  ptr += num_read;

  int answer_val = number1;
  char operation = ' ';
  int number2;

  while (*ptr != '\0' && *ptr != '?') {
    while (isspace((unsigned char)*ptr)) {
      ptr++;
    }

    if (strncmp(ptr, "plus", 4) == 0) {
      operation = '+';
      ptr += 4;
    } else if (strncmp(ptr, "minus", 5) == 0) {
      operation = '-';
      ptr += 5;
    } else if (strncmp(ptr, "multiplied by", 13) == 0) {
      operation = '*';
      ptr += 13;
    } else if (strncmp(ptr, "divided by", 10) == 0) {
      operation = '/';
      ptr += 10;
    } else {
      return false;
    }

    while (isspace((unsigned char)*ptr)) {
      ptr++;
    }

    if (sscanf(ptr, "%d%n", &number2, &num_read) != 1) {
      return false;
    }
    ptr += num_read;

    int temp_result = calculate(answer_val, number2, operation);
    if (operation != ' ' && (temp_result == 0 && (operation == '/' || operation == '*')))
      return false;

    answer_val = temp_result;
  }

  *result = answer_val;
  return true;
}