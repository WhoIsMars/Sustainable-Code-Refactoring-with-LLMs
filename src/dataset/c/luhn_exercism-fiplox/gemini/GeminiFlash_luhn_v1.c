#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>

bool luhn(const char *num) {
  int sum = 0;
  int len = 0;
  bool alt = false;

  // Iterate backwards until non-space character or end of string
  for (const char *p = num; *p != '\0'; ++p) {
    if (isdigit(*p)) {
      len++;
    } else if (*p != ' ') {
      return false;
    }
  }

  if (len <= 1) return false;

  for (const char *p = num + strlen(num) - 1; p >= num; --p) {
    if (*p == ' ') continue;

    int digit = *p - '0';

    if (alt) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }

    sum += digit;
    alt = !alt;
  }

  return (sum % 10 == 0);
}