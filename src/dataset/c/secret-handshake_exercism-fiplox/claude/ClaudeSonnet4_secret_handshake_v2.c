#include "secret_handshake.h"
#include <string.h>
#include <stdlib.h>

static const char *actions[] = { "wink", "double blink", "close your eyes", "jump" };

const char **commands(size_t number)
{
	char **cmds = calloc(4, sizeof(char*));
	size_t pos = 0;
	
	if (number & 16) {
		// Reverse order
		for (int i = 3; i >= 0; --i) {
			if (number & (1 << i)) {
				cmds[pos++] = (char*)actions[i];
			}
		}
	} else {
		// Normal order
		for (int i = 0; i < 4; ++i) {
			if (number & (1 << i)) {
				cmds[pos++] = (char*)actions[i];
			}
		}
	}

	return (const char**)cmds;
}