#include "pangram.h"
#include <ctype.h>

bool is_pangram(const char *sentence)
{
	if (!sentence || !*sentence)
		return false;
	
	unsigned int letter_mask = 0;
	const unsigned int complete_mask = 0x3FFFFFF;
	
	while (*sentence && letter_mask != complete_mask) {
		if (isalpha(*sentence)) {
			letter_mask |= 1U << (tolower(*sentence) - 'a');
		}
		sentence++;
	}
	
	return letter_mask == complete_mask;
}