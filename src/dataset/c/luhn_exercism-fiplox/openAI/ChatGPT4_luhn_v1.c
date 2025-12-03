#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0, digit;
	for (const char *p = num; *p; ++p) {
		if (*p == ' ')
			continue;
		if (!isdigit(*p))
			return false;
		n++;
		digit = *p - '0';
		if (n % 2 == 0) {
			digit *= 2;
			if (digit > 9) digit -= 9;
		}
		sum += digit;
	}
	return n > 1 && sum % 10 == 0;
}