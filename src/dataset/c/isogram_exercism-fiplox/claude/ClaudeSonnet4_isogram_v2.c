#include "isogram.h"

#include <ctype.h>

bool is_isogram(const char phrase[])
{
	if (phrase == NULL) {
		return false;
	}

	unsigned int used = 0;
	int pos;
	while (*phrase) {
		if (isalpha(*phrase)) {
			pos = tolower(*phrase) - 'a';
			if (used & (1u << pos)) {
				return false;
			}
			used |= (1u << pos);
		}
		phrase++;
	}

	return true;
}