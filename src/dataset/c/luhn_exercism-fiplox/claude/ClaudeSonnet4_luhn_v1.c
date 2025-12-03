#include "luhn.h"

#include <ctype.h>
#include <string.h>

bool luhn(const char *num)
{
	int sum = 0, n = 0;
	int digit;
	bool double_next = false;
	
	for (const char *p = num + strlen(num) - 1; p >= num; --p) {
		if (*p == ' ')
			continue;
		if (*p < '0' || *p > '9')
			return false;
		
		digit = *p - '0';
		n++;
		
		if (double_next) {
			digit <<= 1;
			if (digit > 9)
				digit -= 9;
		}
		sum += digit;
		double_next = !double_next;
	}
	return n > 1 && sum % 10 == 0;
}