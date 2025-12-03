#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	char **cmds = malloc(4 * sizeof(char*));
	if (!cmds) return NULL;

	size_t pos = 0;
	size_t i;

	for (i = 0; i < 4; ++i) {
		if (number & (1 << i)) {
			cmds[pos++] = (char*)actions[i];
		}
	}

	if (number & 16) {
		// Reverse the array in-place
		for (size_t i = 0; i < pos / 2; ++i) {
			const char *temp = cmds[i];
			cmds[i] = cmds[pos - 1 - i];
			cmds[pos - 1 - i] = (char*)temp;
		}
	}

	if (pos < 4) {
		cmds = realloc(cmds, (pos + 1) * sizeof(char*));
		if (!cmds) return NULL;
		cmds[pos] = NULL;
	}
	else {
		cmds = realloc(cmds, 5 * sizeof(char*));
		if (!cmds) return NULL;
		cmds[4] = NULL;
	}

	return (const char**)cmds;
}