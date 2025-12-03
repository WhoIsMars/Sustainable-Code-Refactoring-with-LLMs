#include "pangram.h"
#include <ctype.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;
	
	unsigned int used = 0;
	const unsigned int all_letters = 0x3FFFFFF; // 26 bits set
	
	while (*sentence && used != all_letters) {
		if (isalpha(*sentence)) {
			used |= 1U << (tolower(*sentence) - 'a');
		}
		sentence++;
	}
	
	return used == all_letters;
}