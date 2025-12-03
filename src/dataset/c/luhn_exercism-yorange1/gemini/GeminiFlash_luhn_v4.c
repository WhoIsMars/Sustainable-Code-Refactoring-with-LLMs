#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool luhn(const char *num) {
  if (!num) return false;

  size_t len = strlen(num);
  if (len <= 1) return false;

  int sum = 0;
  bool alt = false;
  size_t digit_count = 0;

  for (size_t i = len; i-- > 0;) {
    if (isdigit(num[i])) {
      int digit = num[i] - '0';
      if (alt) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      sum += digit;
      alt = !alt;
      digit_count++;
    } else if (isspace(num[i])) {
      continue;
    } else {
      return false;
    }
  }

  return (digit_count > 1 && sum % 10 == 0);
}