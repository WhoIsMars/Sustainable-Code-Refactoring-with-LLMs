#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;

	unsigned int alphabet_mask = 0;
	int total_letters = 0;

	while (*sentence && total_letters < 26) {
		if (isalpha(*sentence)) {
			int pos = tolower(*sentence) - 'a';
			unsigned int bit = 1U << pos;
			if (!(alphabet_mask & bit)) {
				alphabet_mask |= bit;
				total_letters++;
			}
		}
		sentence++;
	}

	return total_letters == 26;
}