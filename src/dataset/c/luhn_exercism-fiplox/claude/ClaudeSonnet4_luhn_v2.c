#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0;
	int digit;
	const char *p = num;
	
	// Find end of string without strlen
	while (*p) p++;
	
	// Process from end to beginning
	while (--p >= num) {
		if (*p == ' ')
			continue;
		if (*p < '0' || *p > '9')
			return false;
		digit = *p - '0';
		n++;
		if (n & 1) {
			sum += digit;
		} else {
			digit <<= 1;
			sum += digit > 9 ? digit - 9 : digit;
		}
	}
	return n > 1 && sum % 10 == 0;
}