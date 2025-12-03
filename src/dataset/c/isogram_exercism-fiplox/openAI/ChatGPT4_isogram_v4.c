#include "isogram.h"

#include <ctype.h>

bool is_isogram(const char phrase[])
{
	if (!phrase) {
		return false;
	}

	unsigned int used = 0;
	while (*phrase) {
		if (isalpha(*phrase)) {
			int pos = tolower(*phrase) - 'a';
			unsigned int mask = 1U << pos;
			if (used & mask) {
				return false;
			}
			used |= mask;
		}
		phrase++;
	}

	return true;
}