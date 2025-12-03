#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

bool luhn(const char *num) {
  if (num == NULL) {
    return false;
  }

  size_t len = 0;
  while (num[len] != '\0') {
    len++;
  }

  int sum = 0;
  int n = 0;

  for (size_t i = len; i > 0; --i) {
    char c = num[i - 1];

    if (c == ' ') {
      continue;
    }

    if (!isdigit(c)) {
      return false;
    }

    int digit = c - '0';
    n++;

    if (n % 2 == 0) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }
    sum += digit;
  }

  return n > 1 && (sum % 10 == 0);
}