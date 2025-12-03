#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;

	unsigned int seen = 0;
	int total = 0;

	while (*sentence && total < 26) {
		if (isalpha(*sentence)) {
			int pos = tolower(*sentence) - 'a';
			unsigned int mask = 1U << pos;
			if (!(seen & mask)) {
				seen |= mask;
				total++;
			}
		}
		sentence++;
	}

	return total == 26;
}