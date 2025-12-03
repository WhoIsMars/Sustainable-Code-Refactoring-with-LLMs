#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	const char **cmds = malloc(4 * sizeof(char*));
	size_t pos = 0;

	if (cmds == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < 4; ++i) {
		if (number & (1 << i)) {
			cmds[pos++] = actions[i];
		}
	}

	if (number & 16) {
		// Reverse the array in place
		for (size_t i = 0; i < pos / 2; ++i) {
			const char *temp = cmds[i];
			cmds[i] = cmds[pos - 1 - i];
			cmds[pos - 1 - i] = temp;
		}
	}

	if (pos < 4) {
		cmds = realloc(cmds, (pos + 1) * sizeof(char*));
		if (cmds == NULL) {
			return NULL;
		}
		cmds[pos] = NULL;
	}

	return cmds;
}