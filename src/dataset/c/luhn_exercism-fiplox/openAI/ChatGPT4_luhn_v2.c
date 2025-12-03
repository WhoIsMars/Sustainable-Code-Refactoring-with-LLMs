#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0, digit;
	bool alternate = false;

	for (const char *p = num; *p; ++p) {
		if (*p == ' ')
			continue;
		if (!isdigit(*p))
			return false;
		n++;
		digit = *p - '0';
		if (alternate) {
			digit *= 2;
			if (digit > 9)
				digit -= 9;
		}
		sum += digit;
		alternate = !alternate;
	}

	return n > 1 && sum % 10 == 0;
}