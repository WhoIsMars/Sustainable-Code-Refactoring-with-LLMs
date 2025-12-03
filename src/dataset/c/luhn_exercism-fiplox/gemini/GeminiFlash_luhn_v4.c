#include "luhn.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool luhn(const char *num) {
  int sum = 0;
  int len = strlen(num);
  int n = 0;

  for (int i = len - 1; i >= 0; --i) {
    if (isspace(num[i])) {
      continue;
    }

    if (!isdigit(num[i])) {
      return false;
    }

    int digit = num[i] - '0';
    n++;

    if (n % 2 == 0) {
      digit *= 2;
      if (digit > 9) {
        digit -= 9;
      }
    }
    sum += digit;
  }

  return (n > 1) && (sum % 10 == 0);
}