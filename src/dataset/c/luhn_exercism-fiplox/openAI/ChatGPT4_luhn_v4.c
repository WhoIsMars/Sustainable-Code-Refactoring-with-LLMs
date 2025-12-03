#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0, digit, double_digit;
	for (const char *p = num; *p; ++p) {
		if (*p == ' ')
			continue;
		if (!isdigit(*p))
			return false;
		digit = *p - '0';
		if (n++ % 2) {
			double_digit = digit * 2;
			sum += double_digit > 9 ? double_digit - 9 : double_digit;
		} else {
			sum += digit;
		}
	}
	return n > 1 && sum % 10 == 0;
}