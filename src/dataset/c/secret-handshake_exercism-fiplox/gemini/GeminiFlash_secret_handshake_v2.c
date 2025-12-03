#include "secret_handshake.h"
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	const char **cmds = malloc(4 * sizeof(char*));
	size_t pos = 0;

	if (cmds == NULL) {
		return NULL; // Handle memory allocation failure
	}

	if (number & 1) {
		cmds[pos++] = actions[0];
	}
	if (number & 2) {
		cmds[pos++] = actions[1];
	}
	if (number & 4) {
		cmds[pos++] = actions[2];
	}
	if (number & 8) {
		cmds[pos++] = actions[3];
	}

	if (number & 16) {
		// Reverse the array in place
		for (size_t i = 0; i < pos / 2; ++i) {
			const char *temp = cmds[i];
			cmds[i] = cmds[pos - 1 - i];
			cmds[pos - 1 - i] = temp;
		}
	}

	if (pos == 0) {
		free(cmds);
		return NULL;
	}

	return cmds;
}