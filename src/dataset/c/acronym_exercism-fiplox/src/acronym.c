#include "acronym.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *abbreviate(const char *phrase)
{
	if (!phrase || !*phrase)
		return NULL;
	char *abrev = malloc(64);
	char *tmp = abrev;
	*tmp++ = *phrase++;
	while (*phrase) {
		if (*phrase == ' ' || *phrase == '-') {
			while (!isalpha(*phrase))
				phrase++;
			*tmp++ = toupper(*phrase);
	}

		phrase++;
	}
    *tmp = '\0';

	return abrev;
}
