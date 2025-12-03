#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

bool luhn(const char *num) {
  if (!num) return false;

  int sum = 0;
  bool alt = false;
  int n_digits = 0;

  for (const char *c = num; *c; ++c) {
    if (isspace(*c)) continue;

    if (!isdigit(*c)) return false;

    int digit = *c - '0';
    if (alt) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }

    sum += digit;
    alt = !alt;
    n_digits++;
  }

  return (n_digits > 1 && (sum % 10 == 0));
}