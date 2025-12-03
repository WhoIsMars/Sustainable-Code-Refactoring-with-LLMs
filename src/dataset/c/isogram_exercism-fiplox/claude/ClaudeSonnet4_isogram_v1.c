#include "isogram.h"

#include <ctype.h>

bool is_isogram(const char phrase[])
{
	if (phrase == NULL) {
		return false;
	}

	unsigned int used = 0;
	unsigned char c;
	unsigned int bit_pos;
	
	while ((c = *phrase++)) {
		if (isalpha(c)) {
			bit_pos = (tolower(c) - 'a');
			if (used & (1u << bit_pos)) {
				return false;
			}
			used |= (1u << bit_pos);
		}
	}

	return true;
}