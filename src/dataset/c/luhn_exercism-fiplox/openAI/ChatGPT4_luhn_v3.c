#include "luhn.h"

#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0, digit;
	for (const char *p = num + strlen(num) - 1; p >= num; --p) {
		if (*p == ' ')
			continue;
		if (!isdigit(*p))
			return false;
		digit = *p - '0';
		sum += (n++ % 2 == 0) ? digit : (digit > 4 ? digit * 2 - 9 : digit * 2);
	}
	return n > 1 && sum % 10 == 0;
}