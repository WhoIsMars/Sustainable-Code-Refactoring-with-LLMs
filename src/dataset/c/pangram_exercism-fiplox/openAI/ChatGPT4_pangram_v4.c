#include "pangram.h"
#include <ctype.h>
#include <stdbool.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;

	unsigned int alphabet_mask = 0;
	unsigned int full_mask = (1 << 26) - 1;

	while (*sentence) {
		if (isalpha(*sentence)) {
			alphabet_mask |= 1 << (tolower(*sentence) - 'a');
			if (alphabet_mask == full_mask)
				return true;
		}
		sentence++;
	}

	return false;
}