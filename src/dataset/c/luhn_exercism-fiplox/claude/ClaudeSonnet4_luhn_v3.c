#include "luhn.h"

#include <ctype.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0;
	const char *p = num;
	
	while (*p) p++;
	
	for (const char *i = p - 1; i >= num; --i) {
		if (*i == ' ')
			continue;
		if (*i < '0' || *i > '9')
			return false;
		
		int digit = *i - '0';
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