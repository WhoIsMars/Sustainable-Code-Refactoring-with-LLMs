#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

bool luhn(const char *num) {
  if (!num) return false;

  size_t len = 0;
  while (num[len] != '\0') {
    len++;
  }

  if (len <= 1) return false;

  int sum = 0;
  bool need_double = false;
  size_t digit_count = 0;

  for (size_t i = len; i > 0; i--) {
    char c = num[i - 1];
    if (isdigit(c)) {
      int digit = c - '0';
      if (need_double) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      sum += digit;
      need_double = !need_double;
      digit_count++;
    } else if (c == ' ') {
      continue;
    } else {
      return false;
    }
  }

  return (sum % 10 == 0 && digit_count > 1);
}