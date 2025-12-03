#include "isogram.h"

#include <ctype.h>
#include <string.h>

bool is_isogram(const char phrase[])
{
	if (phrase == NULL) {
		return false;
	}

	bool used[27] = {false};
	int pos;
	while (*phrase) {
		if (isalpha(*phrase)) {
			pos = (tolower(*phrase) - 'a') % 26;
			if (used[pos]) {
				return false;
			}
			used[pos] = true;
		}
		phrase++;
	}

	return true;
}