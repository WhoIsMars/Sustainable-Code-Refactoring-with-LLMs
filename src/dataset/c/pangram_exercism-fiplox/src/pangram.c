#include "pangram.h"
#include <ctype.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;
	bool used[26] = {0};
	int pos;

	while (*sentence) {
		if (isalpha(*sentence)) {
			pos = (tolower(*sentence) - 'a') % 26;
			used[pos] = true;
		}
		sentence++;
	}
	for(int i = 0; i < 26; i++) {
		if (!used[i])
			return false;
	}

	return true;
}
