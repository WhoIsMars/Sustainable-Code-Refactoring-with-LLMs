#include "luhn.h"

#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
	int len = strlen(num);
	int sum = 0, n = 0;
	int digit;
	for (int i = len - 1; i >= 0; --i) {
		if (num[i] == ' ')
			continue;
		if (!isdigit(num[i]))
			return false;
		digit = num[i] - '0';
		n++;
		sum += n % 2 ? digit : digit < 9 ? (digit + digit) % 9 : 9;
	}
	return n > 1 && sum % 10 == 0;
}
