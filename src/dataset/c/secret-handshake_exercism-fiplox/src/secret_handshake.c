#include "secret_handshake.h"
#include <string.h>
#include <stdlib.h>

static char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	char **cmds = calloc(4, sizeof(char*));
	size_t i, n, pos = 0;

	for (i = 0; i < 4; ++i) {
		n = (number & 16) ? (4 - 1 - i) : i;
		if (number & 1 << n) {
			cmds[pos++] = actions[n];
		}
	}

	return (const char**)cmds;
}
